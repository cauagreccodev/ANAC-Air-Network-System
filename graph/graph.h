#include "../sparse-matrix/sparse_matrix.h"

#ifndef GRAPH_H
#define GRAPH_H

#define MAX 100
typedef struct Airport{
    char airport_name_vertex[MAX]; //vertice
    char code_vertex[4];
} Airport;

typedef struct Graph{
    Airport *vertex; //vertice
    NodeMatrix **edge; //aresta
    int count;
} Graph;

Graph *create_graph();

int register_airport(Graph *graph, char *airport_name, char *city); //ponteiro de char para receber texto

int register_flight(Graph *graph, int id, char *airport_initial_code, char *airport_final_code);

int remove_flight(Graph *graph, int target_id);

void list_flights(Graph *graph);

int check_flight_ID(Graph *graph, int target_id);

#endif