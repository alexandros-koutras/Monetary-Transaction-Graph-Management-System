#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edges.h"
#include "typedefs.h"


Edge edge_create(uint destination, int ammount, char* date) {
    Edge edge = malloc(sizeof(*edge));
    edge->ammount = ammount;
    strcpy(edge->date, date);
    edge->destination = destination;

    return edge;
}

void edge_edit_ammount(Edge edge, int ammount) {
    edge->ammount = ammount;
}

void edge_edit_date(Edge edge, char* date) {
    strcpy(edge->date, date);
}

void edge_destroy(Edge edge) {
    free(edge);
}