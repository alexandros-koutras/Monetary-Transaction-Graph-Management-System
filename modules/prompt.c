#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>
#include <math.h>
#include "ADTHash.h"
#include "ADTVector.h"
#include "ADTGraph.h"
#include "input.h"

#include "miris.h"


int main() {
    Graph graph = graph_create(NULL);
    HashTable hash = hash_create(NULL);
    read(hash, graph);
    while(1) {
        printf("1. i Ni [Nj Nk ...]\n");
        printf("   insert into the graph structure 1 or more nodes with specific INT ids.\n");
        printf("\n");
        printf("2. n Ni Nj sum date\n");
        printf("   introduce an edge with direction from Ni to Nj with label sum + date if either Ni or Nj does not exist in the graph, do the appropriate node insertion first.\n");
        printf("\n");
        printf("3. d Ni [Nj Nk ...]\n");
        printf("   delete from graph listed nodes Ni, Nj, Nk, etc\n");
        printf("\n");
        printf("4. l Ni Nj\n");
        printf("   remove the edge between Ni and Nj; if there are more than one edges, remove one of the edges.\n");
        printf("\n");
        printf("5. Modify the details of an ongoing transaction!\n");
        printf("   update the values of a specific edge between Ni and Nj\n");
        printf("\n");
        printf("6. f Ni\n");
        printf("   find all outgoing edges from Ni\n");
        printf("\n");
        printf("7. r Ni\n");
        printf("   find all incoming to Ni edges.\n");
        printf("\n");
        printf("8. c Ni\n");
        printf("   find circles Ni is involved in if any\n");
        printf("\n");
        printf("9. fi Ni k\n");
        printf("   find circular relationships in which Ni is involved and moves at least k units of funds.\n");
        printf("\n");
        printf("10. t Ni m\n");
        printf("    find all paths of length upto m for which a flow of transfers can be establsihed from Ni.\n");
        printf("\n");
        printf("11. o Ni Nj\n");
        printf("    If exist, present a path (1) between Ni and Nj\n");
        printf("\n");
        printf("12. e\n");
        printf("    terminate the program.\n");
        printf("\n");
        printf("Enter your choice by typing the correspontand letter or letters!\n");
        printf("\n");

        char choice[3];
        scanf("%2s", choice);


        if (strcmp(choice, "i") == 0 || strcmp(choice, "I") == 0) {
            char yes_no[5];
            uint iban;
            while (1) {
                printf("Please fill in the information required to successfully register on our database!\n");
                printf("INT id: ");
                scanf("%u", &iban);
                printf("\n");
                Vertex new = vertex_create(iban);
                insert(hash, graph, new);
                printf("Success: %d\n", iban);
                printf("Would you like to add another node in the graph? Type yes or no: ");
                scanf("%s", yes_no);
                printf("\n");
                if (strcmp(yes_no, "yes") == 0 || strcmp(yes_no, "YES") == 0 || strcmp(yes_no, "Yes") == 0) {
                    continue;
                } else {
                    break;
                }

            }
        } else if (strcmp(choice, "n") == 0 || strcmp(choice, "N") == 0) {
            char date[11];
            int ammount;
            uint iban1, iban2;
            printf("Please fill in the senders id: ");
            scanf("%d", &iban1);
            printf("Please fill in the recipients id: ");
            scanf("%d", &iban2);            
            Vertex vertex1 = hash_search(hash, iban1);
            Vertex vertex2 = hash_search(hash, iban2);
            if (vertex1 != NULL) {
                if (vertex2 != NULL) {
                    printf("Please fill i the sum you want to transfer: ");
                    scanf("%d", &ammount);
                    printf("And the date of the transaction: ");
                    scanf("%10s", date);
                    insert2(hash, graph, iban1, iban2, ammount, date);
                } else {
                    printf("The recipient does not exist we create the node now\n");
                    insert(hash, graph, vertex2);
                    printf("Please fill i the sum you want to transfer: ");
                    scanf("%d", &ammount);
                    printf("And the date of the transaction: ");
                    scanf("%10s", date);
                    insert2(hash, graph, iban1, iban2, ammount, date);
                }
            } else {
                    printf("The sender does not exist we create the node now\n");
                    insert(hash, graph, vertex1);
                if (vertex2 != NULL) {
                    printf("Please fill i the sum you want to transfer: ");
                    scanf("%d", &ammount);
                    printf("And the date of the transaction: ");
                    scanf("%10s", date);
                    insert2(hash, graph, iban1, iban2, ammount, date);
                } else {
                    printf("The recipient does not exist we create the node now\n");
                    insert(hash, graph, vertex2);
                    printf("Please fill i the sum you want to transfer: ");
                    scanf("%d", &ammount);
                    printf("And the date of the transaction: ");
                    scanf("%10s", date);
                    insert2(hash, graph, iban1, iban2, ammount, date);
                }
            }
        } else if (strcmp(choice, "d") == 0 || strcmp(choice, "D") == 0) {
            while (1) {
                uint iban;
                char yes_no[5];
                printf("Please provide the id of the node you want to remove: ");
                scanf("%u", &iban);
                delete1(hash, graph, iban);
                printf("The node has been successfully deleted\n");
                printf("Would you like to delete another node? Type yes or no\n");
                scanf("%4s", yes_no);
                if (strcmp(yes_no, "yes") == 0 || strcmp(yes_no, "YES") == 0 || strcmp(yes_no, "Yes") == 0) {
                    continue;
                } else {
                    break;
                }
            }
        } else if (strcmp(choice, "l") == 0 || strcmp(choice, "L") == 0) {
            uint iban1, iban2;
            printf("Please provide your id: ");
            scanf("%u", &iban1);
            printf("Now please provide the id of the person the transaction you want to cancel: ");
            scanf("%u", &iban2);
            delete2(hash, graph, iban1, iban2);
            printf("The transaction was successfully canceled!\n");
        } else if (strcmp(choice, "m") == 0 || strcmp(choice, "M") == 0) {
            int ammount, new_ammount;
            char new_date[11];
            uint iban1, iban2;
            printf("Please provide your id: ");
            scanf("%u", &iban1);
            printf("What's the id of the person the transaction is going to: ");
            scanf("%u", &iban2);
            printf("What's the current ammount of the transaction: ");
            scanf("%d", &ammount);
            printf("And what's the new ammount you want to set on the transaction: ");
            scanf("%d", &new_ammount);
            printf("What's the new date: ");
            scanf("%10s", new_date);
            modify(hash, graph, iban1, iban2, ammount, new_ammount, new_date);
            printf("New ammount has been set successfully\n");
        } else if (strcmp(choice, "f") == 0 || strcmp(choice, "F") == 0) {
            uint iban;
            printf("Please provide your id so we can find all outgoing edges: ");
            scanf("%u", &iban);
            find(hash, graph, iban);
        } else if (strcmp(choice, "r") == 0 || strcmp(choice, "R") == 0) {
            uint iban;
            printf("Please provide your id so we can find all the incoming edges: ");
            scanf("%u", &iban);
            receiving(hash, graph, iban);
        } else if (strcmp(choice, "c") == 0 || strcmp(choice, "C") == 0) {
            uint iban;

            printf("Please provide your id: ");
            scanf("%u", &iban);
            circlefind(hash, graph, iban);
        } else if (strcmp(choice, "fi") == 0 || strcmp(choice, "Fi") == 0 || strcmp(choice, "FI") == 0) {
            uint iban;
            int min_sum;

            printf("Please provide your id: ");
            scanf("%u", &iban);
            printf("And a min_sum: ");
            scanf("%d", &min_sum);
            findcircles(hash, graph, iban, min_sum);
        } else if (strcmp(choice, "t") == 0 || strcmp(choice, "T") == 0) {
            uint iban;
            int path_size;

            printf("Please provide your id: ");
            scanf("%u", &iban);
            printf("And the size of path: ");
            scanf("%d", &path_size);

            traceflow(hash, graph, iban, path_size);
        } else if (strcmp(choice, "o") == 0 || strcmp(choice, "O") == 0) {
            uint iban1, iban2;
            printf("Please provide your id: ");
            scanf("%u", &iban1);
            printf("And the id of the other node: ");
            scanf("%u", &iban2);

            connected(hash, graph, iban1, iban2);
        } else if (strcmp(choice, "e") == 0 || strcmp(choice, "E") == 0) {
            printf("Thank you for using our services!\n");
            //exit(graph);
        } else {
            printf("Unrecognized command\n");
        }

    }
}


