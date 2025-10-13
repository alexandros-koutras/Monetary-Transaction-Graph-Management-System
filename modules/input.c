#include <stdio.h>
#include <stdlib.h>

#include "ADTHash.h"
#include "miris.h"
#include "vertices.h"


int read(HashTable hash, Graph graph) {
    FILE* file;
    uint iban1, iban2;
    int ammount;
    char date[11];

    file = fopen("init.txt", "r");
    
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (!feof(file)) {
        for (int i = 0; i < 4; i++) {
            if (i == 0) {
                if (fscanf(file, "%d", &iban1) == 1) {
                    Vertex vertex = hash_search(hash, iban1);
                    if (vertex != NULL) {
                        printf("person already exists yeahhh\n");
                        continue;
                    } else {
                        printf("person doesnt exist:(\n");
                        printf("sender %d\n", iban1);
                        vertex = vertex_create(iban1);
                        insert(hash, graph, vertex);
                        hash_insert(hash, vertex);
                    }
                } else {
                    break;
                }
            } else if (i == 1) {
                fscanf(file, "%d", &iban2);
                Vertex vertex = hash_search(hash, iban2);
                if (vertex != NULL) {
                    printf("person already exists yeahhh\n");
                    continue;
                } else {
                    printf("person doesnt exist:(\n");
                    printf("reciepient %d\n", iban2);
                    vertex = vertex_create(iban2);
                    insert(hash, graph, vertex);
                    hash_insert(hash, vertex);
                }
            } else if (i == 2) {
                fscanf(file, "%d", &ammount);
                printf("ammount %d\n", ammount);
            } else if (i == 3) {
                fscanf(file, "%10s", date);
                printf("date %10s\n", date);
                insert2(hash, graph, iban1, iban2, ammount, date);
            }
        }
    }

    fclose(file);

    return 0;
}