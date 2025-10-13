#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ADTHash.h"
#include "vertices.h"
#include "ADTList.h"
#include "ADTVector.h"

#define MAX 50

static int bucket_id_counter = 0;

int* create_int(int value) {
    int *ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed for int\n");
        exit(EXIT_FAILURE);
    }
    *ptr = value;
    return ptr;
}

int compare_void_int(Pointer ptr, int value) {
    if (ptr == NULL) {
        return 0;
    }
    int stored_value = *(int*)ptr;
    return (stored_value == value);
}

int compare_ints(Pointer a, Pointer b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return (int_a > int_b) - (int_a < int_b);  // Compact comparison
}

void print_integer(Pointer ptr) {
    if (ptr != NULL) {
        int value = *(int*)ptr;
        printf("old_bucket_hash[i] = %d\n", value);
    }
}

void print_integer1(Pointer ptr) {
    if (ptr != NULL) {
        int value = *(int*)ptr;
        printf("new_bucket_hash[i] = %d\n", value);
    }
}

Bucket bucket_create(int local_depth, int count) {
    Bucket bucket = malloc(sizeof(*bucket));
    if (bucket == NULL) {
        fprintf(stderr, "Memory allocation failed for bucket\n");
        exit(EXIT_FAILURE);
    }

    bucket->count = count;
    bucket->local_depth = local_depth;
    bucket->verteces = list_create(NULL);
    bucket->buddies = list_create(NULL);
    bucket->id = bucket_id_counter++;

    return bucket;
}

uint hash_function(int key, int depth) {
    uint hash_value = key * 2654435761 % (1 << 31);
    return (hash_value >> (31 - depth)) & ((1 << depth) - 1);
}

HashTable hash_create(DestroyFunc destroy_value) {
    HashTable hash = malloc(sizeof(*hash));
    if (hash == NULL) {
        fprintf(stderr, "Memory allocation failed for hash table\n");
        exit(EXIT_FAILURE);
    }

    hash->directory = vector_create(50, NULL);
    if (hash->directory == NULL) {
        fprintf(stderr, "Memory allocation failed for directory\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 50; i++) {
        Bucket bucket = bucket_create(1, 0);
        list_insert(bucket->buddies, create_int(i));
        hash->directory->array[i].value = bucket;
    }

    hash->size = 50;
    hash->global_depth = 1;

    return hash;
}

void split_bucket(HashTable hash, Bucket bucket, uint old_hash_key) {
    printf("  Splitting bucket ID %d at hash key %u with local depth %d\n", bucket->id, old_hash_key, bucket->local_depth);
    bucket->local_depth++;

    Pointer old_bucket_hash[list_size(bucket->buddies) / 2];
    Pointer new_bucket_hash[list_size(bucket->buddies) / 2];  // Corrected assignment for new bucket

    int counter = 0, iterate = 0;

    for (ListNode node = list_first(bucket->buddies); node != NULL; node = list_next(bucket->buddies, node)) {
        if (counter < list_size(bucket->buddies) / 2) {
            old_bucket_hash[counter++] = node->value;
            print_integer(old_bucket_hash[counter - 1]);
        } else {
            new_bucket_hash[iterate++] = node->value;
            print_integer1(new_bucket_hash[iterate - 1]);  // Corrected iterate index
        }
    }

    Bucket new_bucket = bucket_create(bucket->local_depth, 0);
    List new_buddies = list_create(NULL);
    int flag = 0;

    ListNode node = list_first(bucket->verteces);
    while (node != NULL) {
        flag = 0;
        Vertex v = node->value;
        uint new_hash_key = hash_function(v->iban, hash->global_depth);
        ListNode next_node = list_next(bucket->verteces, node);

        for (int i = 0; i < list_size(bucket->buddies) / 2; i++) {
            print_integer(old_bucket_hash[i]);
            if (compare_void_int(old_bucket_hash[i], new_hash_key)) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            list_insert(new_bucket->verteces, v);
            new_bucket->count++;
            list_delete(bucket->verteces, node);
            bucket->count--;
            hash->directory->array[new_hash_key].value = new_bucket;

            if (list_find(new_bucket->buddies, create_int(new_hash_key), compare_ints) == NULL) {
                list_insert(new_bucket->buddies, create_int(new_hash_key));
            }
            printf("    Moving iban %d to new bucket ID %d with hash key %u\n", v->iban, new_bucket->id, new_hash_key);
        } else {
            hash->directory->array[new_hash_key].value = bucket;

            if (list_find(new_buddies, create_int(new_hash_key), compare_ints) == NULL) {
                list_insert(new_buddies, create_int(new_hash_key));
            }
        }
        node = next_node;
    }

    bucket->buddies = new_buddies;
}

void double_directory(HashTable hash) {
    printf("Doubling directory size from %d to %d\n", hash->size, hash->size * 2);

    Vector all_buckets = vector_create(0, NULL);
    if (all_buckets == NULL) {
        fprintf(stderr, "Memory allocation failed for all_buckets\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (i < hash->size) {
        Bucket b = hash->directory->array[i].value;
        vector_insert_last(all_buckets, b);
        int buddies = (int)pow(2.0, (double)(hash->global_depth - b->local_depth));
        i += buddies;
    }

    hash->global_depth++;
    hash->size *= 2;

    for (int i = hash->size / 2; i < hash->size; i++) {
        vector_insert_last(hash->directory, NULL);
    }

    int j = 0, buddies = 0;
    i = 0;
    while (i < hash->size) {
        Bucket b = all_buckets->array[j].value;
        if (buddies == 0) {
            buddies = (int)pow(2.0, (double)(hash->global_depth - b->local_depth));
        }
        hash->directory->array[i].value = b;
        if (list_find(b->buddies, create_int(i), compare_ints) == NULL) {
            list_insert(b->buddies, create_int(i));
        }
        printf("  Directory entry %d now points to bucket ID %d with local depth %d\n", i, b->id, b->local_depth);
        buddies--;
        i++;
        if (buddies == 0) {
            j++;
        }
    }
}

void hash_insert(HashTable hash, Vertex vertex) {
    uint hash_key = hash_function(vertex->iban, hash->global_depth);
    printf("\nInserting iban %d with hash key %u\n", vertex->iban, hash_key);

    Bucket bucket = hash->directory->array[hash_key].value;
    if (bucket == NULL) {
        fprintf(stderr, "Error: Bucket is NULL for hash_key %u\n", hash_key);
        return;
    }

    if (bucket->count < MAX) {
        list_insert(bucket->verteces, vertex);
        bucket->count++;
        printf("  Inserting into bucket with id %d (current count %d)\n", bucket->id, bucket->count);
    } else if (bucket->count >= MAX) {
        if (bucket->local_depth < hash->global_depth) {
            printf("  Splitting bucket due to overflow\n");
            list_insert(bucket->verteces, vertex);
            bucket->count++;
            split_bucket(hash, bucket, hash_key);
        } else {
            printf("  Doubling directory due to overflow and max local depth\n");
            double_directory(hash);
            hash_insert(hash, vertex);  // Re-insert after expanding directory
        }
    }
    printf("Inserted iban %d\n", vertex->iban);
}

Vertex hash_search(HashTable hash, uint iban) {
    uint hash_key = hash_function(iban, hash->global_depth);
    Bucket bucket = hash->directory->array[hash_key].value;

    if (bucket == NULL) {
        fprintf(stderr, "Error: Bucket is NULL for hash_key %u\n", hash_key);
        return NULL;
    }

    printf("Searching...\n");
    for (ListNode node = list_first(bucket->verteces); node != NULL; node = list_next(bucket->verteces, node)) {
        Vertex vertex = node->value;
        if (vertex->iban == iban) {
            return vertex;
        }
    }
    return NULL;
}
