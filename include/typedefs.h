#pragma once    //include το πολύ μία φορά

typedef unsigned int uint;

typedef void* Pointer;

typedef void (*DestroyFunc)(Pointer value);

typedef int (*CompareFunc)(Pointer a, Pointer b);

typedef struct list_node* ListNode;

typedef struct list* List;

typedef struct edge* Edge;

typedef struct vertex* Vertex;

typedef struct graph* Graph;

typedef struct bucket* Bucket;

typedef struct hash_table* HashTable;

typedef struct vector_node* VectorNode;

typedef struct vector* Vector;
