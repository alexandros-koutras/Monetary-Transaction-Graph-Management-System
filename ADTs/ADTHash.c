#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ADTHash.h"
#include "vertices.h"
#include "ADTList.h"
#include "ADTVector.h"

#define MAX 3

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
    if (ptr == NULL) return 0;
    return (*(int*)ptr == value);
}

int compare_ints(Pointer a, Pointer b) {
    return (*(const int*)a > *(const int*)b) - (*(const int*)a < *(const int*)b);
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
    hash->directory = vector_create(2, NULL);
    if (hash->directory == NULL) {
        fprintf(stderr, "Memory allocation failed for directory\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; i++) {
        Bucket bucket = bucket_create(1, 0);
        list_insert(bucket->buddies, create_int(i));
        hash->directory->array[i].value = bucket;
    }

    hash->size = 2;
    hash->global_depth = 1;
    return hash;
}

void split_bucket(HashTable hash, Bucket bucket, uint old_hash_key) {
    printf("Splitting bucket ID %d at hash key %u with local depth %d\n", bucket->id, old_hash_key, bucket->local_depth);
    
    bucket->local_depth++;  // Increase local depth of this bucket

    // Create a new bucket with the same local depth
    Bucket new_bucket = bucket_create(bucket->local_depth, 0);
    List new_buddies = list_create(NULL);  // New buddies list for the new bucket

    // Split buddy hashes
    int half_size = list_size(bucket->buddies) / 2;
    Pointer old_bucket_hash[half_size];
    int counter = 0;

    for (ListNode node = list_first(bucket->buddies); node != NULL; node = list_next(bucket->buddies, node)) {
        if (counter < half_size) {
            old_bucket_hash[counter++] = node->value;
        }
    }

    // Reassign vertices based on new hashes
    ListNode node = list_first(bucket->verteces);
    while (node != NULL) {
        Vertex v = node->value;
        uint new_hash_key = hash_function(v->iban, hash->global_depth);
        ListNode next_node = list_next(bucket->verteces, node);

        int in_old_bucket = 0;
        for (int i = 0; i < half_size; i++) {
            if (compare_void_int(old_bucket_hash[i], new_hash_key)) {
                in_old_bucket = 1;
                break;
            }
        }

        if (in_old_bucket) {
            // Remains in the original bucket
            hash->directory->array[new_hash_key].value = bucket;
            if (list_find(bucket->buddies, create_int(new_hash_key), compare_ints) == NULL) {
                list_insert(bucket->buddies, create_int(new_hash_key));
            }
        } else {
            // Move to new bucket
            list_insert(new_bucket->verteces, v);
            new_bucket->count++;
            list_delete(bucket->verteces, node);
            bucket->count--;
            hash->directory->array[new_hash_key].value = new_bucket;
            if (list_find(new_bucket->buddies, create_int(new_hash_key), compare_ints) == NULL) {
                list_insert(new_bucket->buddies, create_int(new_hash_key));
            }
        }
        node = next_node;
    }

    // Update buddies list for the original bucket
    bucket->buddies = new_buddies;
}

void double_directory(HashTable hash) {
    printf("Doubling directory size from %d to %d\n", hash->size, hash->size * 2);
    
    Vector new_directory = vector_create(hash->size * 2, NULL);
    if (new_directory == NULL) {
        fprintf(stderr, "Memory allocation failed for new directory\n");
        exit(EXIT_FAILURE);
    }

    // Copy old directory to new with expanded capacity
    for (int i = 0; i < hash->size; i++) {
        Bucket bucket = hash->directory->array[i].value;
        int step = 1 << (hash->global_depth - bucket->local_depth);
        
        for (int j = 0; j < step; j++) {
            new_directory->array[i + j * hash->size].value = bucket;
        }
    }

    vector_destroy(hash->directory);  // Free the old directory memory
    hash->directory = new_directory;
    hash->global_depth++;
    hash->size *= 2;
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
    } else if (bucket->local_depth < hash->global_depth) {
        list_insert(bucket->verteces, vertex);
        bucket->count++;
        split_bucket(hash, bucket, hash_key);
    } else {
        double_directory(hash);  // Expand the directory
        hash_insert(hash, vertex);  // Re-attempt the insertion after directory expansion
    }
}


Vertex hash_search(HashTable hash, uint iban) {
    uint hash_key = hash_function(iban, hash->global_depth);
    Bucket bucket = hash->directory->array[hash_key].value;

    if (bucket == NULL) {
        return NULL;
    }

    for (ListNode node = list_first(bucket->verteces); node != NULL; node = list_next(bucket->verteces, node)) {
        if (((Vertex)node->value)->iban == iban) {
            return node->value;
        }
    }
    return NULL;
}
