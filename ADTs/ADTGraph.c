#include <stdio.h>
#include <stdlib.h>

#include "ADTGraph.h"
#include "ADTHash.h"
#include "compare_funcs.h"
#include "typedefs.h"



Graph graph_create(DestroyFunc destroy_value) {
    Graph graph = malloc(sizeof(*graph));

    List vertices = list_create(NULL);

    graph->vertices = vertices;
    graph->size = 0;

    return graph;
}

void graph_insert_vertex(Graph graph, Vertex vertex) {
    list_insert(graph->vertices, vertex);
}

void graph_insert_edge(Graph graph, Vertex vertex, Edge edge) {
    list_insert(vertex->edges, edge);
}

void graph_delete_vertex(Graph graph, Vertex vertex) {
    Vertex iterate_vertex;
    Edge iterate_edge;

    // Iterate over each vertex in the graph
    for (ListNode node = list_first(graph->vertices); node != NULL; node = list_next(graph->vertices, node)) {
        iterate_vertex = node->value;
        printf("Checking vertex...\n");
        // Iterate over each edge in the vertex's edges list
        for (ListNode edge_node = list_first(iterate_vertex->edges); edge_node != NULL;) {
            iterate_edge = edge_node->value;
            // Check if destination matches the target iban
            if (iterate_edge->destination == vertex->iban) {
                ListNode temp = list_next(iterate_vertex->edges, edge_node);  // Save the next node
                list_delete(iterate_vertex->edges, edge_node);  // Delete the current edge
                printf("Edge deleted for destination %d\n", vertex->iban);
                edge_node = temp;  // Move to the next node
            } else {
                edge_node = list_next(iterate_vertex->edges, edge_node);  // Move to the next node
            }
        }
    }

    // Delete the vertex from the graph's vertices list
    list_delete(graph->vertices, list_find_node(graph->vertices, vertex, compare_vertices));
}


void graph_delete_edge(Graph graph, Vertex vertex, Edge edge) {
    Edge soon_to_be_deleted = malloc(sizeof(*soon_to_be_deleted));
    for (ListNode node = vertex->edges->dummy->next; node != NULL; node = node->next) {

        soon_to_be_deleted = node->value;
        if (soon_to_be_deleted->destination == edge->destination) {
            list_delete(vertex->edges, node);
            break;
        }
    }
}

void graph_new_transaction_info(Graph graph, Edge edge, int sum, char* date) {
    edge_edit_ammount(edge, sum);
    edge_edit_date(edge, date);
}

void graph_show_out_edges(Graph graph, Vertex vertex) {
    for (ListNode node = vertex->edges->dummy->next; node != NULL; node = node->next) {
        Edge edge = node->value;
        printf("%d  %d  %d  %10s\n", vertex->iban, edge->destination, edge->ammount, edge->date);
    }
}

void graph_show_in_edges(Graph graph, Vertex vertex) {
    Vertex iterate_vertex = malloc(sizeof(*iterate_vertex));
    Edge iterate_edge = malloc(sizeof(*iterate_edge));

    for (ListNode node = graph->vertices->dummy->next; node != NULL; node = node->next) {
        iterate_vertex = node->value;
        if (iterate_vertex->iban == vertex->iban) {
            continue;
        }
        for (ListNode edge_node = iterate_vertex->edges->dummy->next; edge_node != NULL; edge_node = edge_node->next) {
            iterate_edge = edge_node->value;
            if (iterate_edge->destination == vertex->iban) {
                printf("%d  %d  %d  %10s\n", iterate_vertex->iban, vertex->iban, iterate_edge->ammount, iterate_edge->date);
            }
        }
    }
}

int graph_DFS(Graph graph, Vertex vertex, List visited, List recStack) {
    list_insert(visited, vertex);
    list_insert(recStack, vertex);

    for (ListNode node = vertex->edges->dummy->next; node != NULL; node = node->next) {
        Edge edge = node->value;
        Vertex temp1 = vertex_create(edge->destination);
        Vertex temp = list_find(graph->vertices, temp1, compare_vertices);

        if (temp == NULL) {
            continue;
        }

        if (list_find(visited, temp, compare_vertices) == NULL) {
            if (graph_DFS(graph, temp, visited, recStack)) {
                return 1;
            }
        } else if (list_find(recStack, temp, compare_vertices) != NULL) {
                return 1;
        }
    }

    list_delete(recStack, list_find_node(recStack, vertex, compare_vertices));

    return 0;
}



int graph_DFS2(Graph graph, Vertex vertex, List visited, List recStack, int min_sum) {
    list_insert(visited, vertex);
    list_insert(recStack, vertex);

    for (ListNode node = vertex->edges->dummy->next; node != NULL; node = node->next) {
        Edge edge = (Edge)node->value;

        if (edge->ammount < min_sum) {
            continue;  // Skip edges with weight less than min_sum
        }

        // Look up destination vertex directly in graph's vertex list
        Vertex temp = list_find(graph->vertices, create_int(edge->destination), compare_vertices);

        if (temp == NULL) {
            continue;  // If the destination vertex is not found, skip this edge
        }

        if (list_find(visited, temp, compare_vertices) == NULL) {
            // If vertex not visited, perform DFS on this vertex
            if (graph_DFS2(graph, temp, visited, recStack, min_sum)) {
                return 1;  // Cycle found
            }
        } else if (list_find(recStack, temp, compare_vertices) != NULL) {
            return 1;  // Cycle detected through recursion stack
        }
    }

    // Remove vertex from recursion stack
    ListNode recNode = list_find_node(recStack, vertex, compare_vertices);
    if (recNode) {
        list_delete(recStack, recNode);
    }
    
    return 0;  // No cycle found
}


void graph_DFS3(Graph graph, Vertex vertex, List visited, List path, int depth, int max_depth) {
    list_insert(visited, vertex);
    list_insert(path, vertex);

    printf("%d\n", vertex->iban);

    if (depth < max_depth) {
        for (ListNode node = vertex->edges->dummy->next; node != NULL; node = node->next) {
            Edge edge = node->value;
            Vertex temp1 = vertex_create(edge->destination);
            Vertex temp = list_find(graph->vertices, temp1, compare_vertices);

            if (temp == NULL) {
                continue;  // Skip if the destination vertex is not found
            }

            // If the adjacent vertex is not visited, recurse on it
            if (list_find(visited, temp, compare_vertices) == NULL) {
                graph_DFS3(graph, temp, visited, path, depth + 1, max_depth);
            }
        }
    }
}

void graph_connected(Graph graph, Vertex vertex, Edge edge) {
    for(ListNode node = vertex->edges->dummy->next; node != NULL; node = node->next) {
        Edge curr_edge = node->value;
        if (curr_edge->destination == edge->destination) {
            printf("Connected graph\n");
            break;
        }
    }
}

void graph_destroy() {

}