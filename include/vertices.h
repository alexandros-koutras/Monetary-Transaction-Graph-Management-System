#include "typedefs.h"


struct vertex {
    uint iban;
    List edges;
};



Vertex vertex_create(uint iban);

void vertex_modify_iban(Vertex vertex, uint iban);

void vertex_destroy(Vertex vertex);