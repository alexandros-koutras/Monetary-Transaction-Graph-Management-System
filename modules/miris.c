#include <stdio.h>
#include <stdlib.h>

#include "ADTGraph.h"
#include "ADTHash.h"
#include "compare_funcs.h"


void insert(HashTable hash, Graph graph, Vertex vertex) {
    graph_insert_vertex(graph, vertex);
    hash_insert(hash, vertex);
}

void insert2(HashTable hash, Graph graph, uint iban1, uint iban2, int ammount, char date[]) {
    Vertex remitter = hash_search(hash, iban1);
    // Vertex remitter = list_find(graph->vertices, temp_vertex, compare_vertices);
    Edge recipient = edge_create(iban2, ammount, date);
    graph_insert_edge(graph, remitter, recipient);
}

void delete1(HashTable hash, Graph graph, uint iban) {
    Vertex delete_vertex = hash_search(hash, iban);
    // Vertex delete_vertex = list_find(graph->vertices, temp_vertex, compare_vertices);

    graph_delete_vertex(graph, delete_vertex);
}

void delete2(HashTable hash, Graph graph, uint iban1, uint iban2) {
    Edge temp_edge = edge_create(iban2, 0, "a");
    Vertex vertex = hash_search(hash, iban1);

    Edge edge = list_find(vertex->edges, temp_edge, compare_edges);

    graph_delete_edge(graph, vertex, edge);
}

void modify(HashTable hash, Graph graph, uint iban1, uint iban2, int ammount, int new_ammount, char new_date[]) {
    Edge temp_edge = edge_create(iban2, 0, "a");
    Vertex vertex = hash_search(hash, iban1);

    Edge edge = list_find(vertex->edges, temp_edge, compare_edges);

    graph_new_transaction_info(graph, edge, new_ammount, new_date);
}

void find(HashTable hash, Graph graph, uint iban) {
    Vertex vertex = hash_search(hash, iban);

    graph_show_out_edges(graph, vertex);
}

void receiving(HashTable hash, Graph graph, uint iban) {
    Vertex vertex = hash_search(hash, iban);

    graph_show_in_edges(graph, vertex);
}

void circlefind(HashTable hash, Graph graph, uint iban) {
    int cycle;

    Vertex vertex = hash_search(hash, iban);
    List visited = list_create(NULL);
    List recStack = list_create(NULL);

    cycle = graph_DFS(graph, vertex, visited, recStack);

    if (cycle == 1) {
        printf("Found a cycle\n");
    } else {
        printf("No cycle found\n");
    }
}

void findcircles(HashTable hash, Graph graph, uint iban, int min_sum) {
    Vertex vertex = hash_search(hash, iban);
    List visited = list_create(NULL);
    List recStack = list_create(NULL);

    int circle = graph_DFS2(graph, vertex, visited, recStack, min_sum);

    if (circle == 1) {
        printf("Found a cycle\n");
    } else {
        printf("No cycle found\n");
    }
}

void traceflow(HashTable hash, Graph graph, uint iban, int path_size) {
    Vertex vertex = hash_search(hash, iban);
    List visited = list_create(NULL);
    List path = list_create(NULL);

    graph_DFS3(graph, vertex, visited, path, 0, path_size);
}

void connected(HashTable hash, Graph graph, uint iban1, uint iban2) {
    Edge temp_edge = edge_create(iban2, 0, "a");
    Vertex vertex = hash_search(hash, iban1);
    Edge edge = list_find(vertex->edges, temp_edge, compare_edges);

    graph_connected(graph, vertex, edge);
}

void exit1(Graph graph) {

}