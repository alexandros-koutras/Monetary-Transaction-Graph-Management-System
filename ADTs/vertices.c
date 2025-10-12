#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADTList.h"
#include "vertices.h"
#include "typedefs.h"


Vertex vertex_create(uint iban) {
    Vertex vertex = malloc(sizeof(*vertex));
    List edges = list_create(NULL);

    vertex->iban = iban;
    vertex->edges = edges;

    return vertex;
}

void vertex_modify_iban(Vertex vertex, uint iban) {
    vertex->iban = iban;
}

void vertex_destroy(Vertex vertex) {
    list_destroy(vertex->edges);
    free(vertex);
}