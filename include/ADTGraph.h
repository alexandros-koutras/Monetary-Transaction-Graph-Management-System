#include <stdio.h>
#include <stdlib.h>

#include "ADTList.h"
#include "vertices.h"
#include "edges.h"
#include "typedefs.h"


struct graph {
    List vertices;
    int size;
};

Graph graph_create(DestroyFunc destroy_value);

void graph_insert_vertex(Graph graph, Vertex vertex);

void graph_insert_edge(Graph graph, Vertex vertex, Edge edge);

void graph_delete_vertex(Graph graph, Vertex vertex);

void graph_delete_edge(Graph graph, Vertex vertex, Edge edge);

void graph_new_transaction_info(Graph graph, Edge edge, int sum, char* date);

void graph_show_out_edges(Graph graph, Vertex vertex);

void graph_show_in_edges(Graph graph, Vertex vertex);

int graph_DFS(Graph graph, Vertex vertex, List visited, List recStack);

int graph_DFS2(Graph graph, Vertex vertex, List visited, List recStack, int min_sum);

void graph_DFS3(Graph graph, Vertex vertex, List visited, List path, int depth, int max_depth);

void graph_connected(Graph graph, Vertex vertex, Edge edge);

void graph_destroy();