#include "typedefs.h"


// void insert(Graph graph, char name[], char surname[], int iban);

void insert(HashTable hash, Graph graph, Vertex vertex);

void insert2(HashTable hash, Graph graph, uint iban1, uint iban2, int ammount, char date[]);

void delete1(HashTable hash, Graph graph, uint iban);

void delete2(HashTable hash, Graph graph, uint iban1, uint iban2);

void modify(HashTable hash, Graph graph, uint iban1, uint iban2, int ammount, int new_ammount, char new_date[]);

void find(HashTable hash, Graph graph, uint iban);

void receiving(HashTable hash, Graph graph, uint iban);

void circlefind(HashTable hash, Graph graph, uint iban);

void findcircles(HashTable hash, Graph graph, uint iban, int min_sum);

void traceflow(HashTable hash, Graph graph, uint iban, int path_size);

void connected(HashTable hash, Graph graph, uint iban1, uint iban2);

// void exit(Graph graph);