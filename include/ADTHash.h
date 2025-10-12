#include <typedefs.h>


struct bucket {
    int id;
    int local_depth;
    int count;
    List verteces;
    List buddies;
};

struct hash_table {
    int global_depth;
    int size;
    Vector directory;
};

int* create_int(int value);

void print_integer(void* ptr);

int compare_void_int(void* ptr, int value);

int compare_ints(Pointer a, Pointer b);

Bucket bucket_create(int local_depth, int count);

uint hash_function(int key, int depth);

HashTable hash_create(DestroyFunc destroy_value);

void split_bucket(HashTable hash, Bucket bucket, uint old_hash_key);

void double_directory(HashTable hash);

void hash_insert(HashTable hash, Vertex vertex);

Vertex hash_search(HashTable hash, uint iban);