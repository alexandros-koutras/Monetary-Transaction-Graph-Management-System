#include "vertices.h"
#include "edges.h"
#include "ADTHash.h"
#include "typedefs.h"


int compare_vertices(Pointer a, Pointer b) {
    Vertex vertexA = (Vertex)a;
    Vertex vertexB = (Vertex)b; 
	return vertexA->iban - vertexB->iban;
}

int compare_edges(Pointer a, Pointer b) {
    Edge edgeA = (Edge)a;
    Edge edgeB = (Edge)b; 
	return edgeA->destination - edgeB->destination;
}

int compare(Pointer a, Pointer b) {
	return a - b;
}