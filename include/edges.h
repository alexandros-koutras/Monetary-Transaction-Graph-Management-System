#include "typedefs.h"


struct edge {
    uint destination;
    int ammount;
    char date[11];
};



Edge edge_create(uint destination, int ammount, char* date);

void edge_edit_ammount(Edge edge, int ammount);

void edge_edit_date(Edge edge, char* date);

void edge_destroy(Edge edge);