#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "../sparse-matrix/sparse_matrix.h"

Graph *create_graph(){
    Graph *p = malloc(sizeof(Graph));
    p->count = 0;
    p->edge = create_matrix(MAX);
    p->vertex = malloc(MAX * sizeof(Airport));
    return p;
}

int register_airport(Graph *graph, char *airport_name, char *city){
    if(graph->count >= MAX){
        return 0;
    }
    strcpy(graph->vertex[graph->count].code_vertex, airport_name);
    strcpy(graph->vertex[graph->count].airport_name_vertex, city);
    graph->count++;
    return 1;
}

int register_flight(Graph *graph, int id, char *airport_initial_code, char *airport_final_code){ //origem e destino
    int row = -1;
    int column = -1;
    
    for (int i = 0; i < graph->count; i++){
        if(strcmp(graph->vertex[i].code_vertex, airport_initial_code) == 0){
            row = i;
        }
        if(strcmp(graph->vertex[i].code_vertex, airport_final_code) == 0){
            column = i;
        }
    }
    
    if(row != -1 && column != -1){
        int *flight_id = malloc(sizeof(int)); //aloca espaco para id por a matriz recebe void
        *flight_id = id;

        add_data(graph->edge, flight_id, row, column); //insere a aresta na sparse_matrix usando add_data
        return 1;
    }
    return 0; //falha (um dos aeroportos nao existe)
}

int remove_flight(Graph *graph, int target_id){
    for(int i = 0; i < graph->count; i++){
        NodeMatrix *p_current = graph->edge[i];
        NodeMatrix *prev = NULL;
        while(p_current != NULL && *(int*)p_current->data != target_id){
            prev = p_current;
            p_current = p_current->next;
        }
        if(p_current == NULL){
            continue;
        }
        if(prev == NULL){
            graph->edge[i] = p_current->next;
        }
        else{
            prev->next = p_current->next;
        }
        free(p_current->data);
        return 1;
    }
    return 0;
}

void list_flights(Graph *graph){
    int has_flights = 0;

    for(int i = 0; i < graph->count; i++){
        NodeMatrix *p_current = graph->edge[i];

        if(p_current == NULL){
            continue;
        }

        has_flights = 1;
        printf("\n--- Flights departing from %s ---\n", graph->vertex[i].code_vertex);

        while(p_current != NULL){
            printf("Destination: %s (Flight ID: %d)\n", graph->vertex[p_current->column].code_vertex, *(int*)p_current->data);
            p_current = p_current->next;
        }
    }

    if(has_flights == 0){
        printf("\nNo flights registered.\n");
    }
}

int check_flight_ID(Graph *graph, int target_id){
    for(int i = 0; i < graph->count; i++){
        NodeMatrix *p_current = graph->edge[i];
        while(p_current != NULL){
            if(*(int*)p_current->data == target_id){
                return 1;
            }
            p_current = p_current->next;
        }
    }
    return 0;
}

void find_paths(Graph *graph, int current_vertex, int dest_vertex, int visited[], int path[], int path_index, int *found){
    visited[current_vertex] = 1;
    path[path_index] = current_vertex;
    path_index++;

    if(current_vertex == dest_vertex){
        printf("\nRoute found: ");
        for(int i = 0; i < path_index; i++){
            printf("%s", graph->vertex[path[i]].code_vertex);
            if(i < path_index - 1){
                printf(" -> ");
            }
        }
        printf("\n");
        *found = 1;
    }
    else{
        NodeMatrix *p_current = graph->edge[current_vertex];
        while(p_current != NULL){
            if(visited[p_current->column] == 0){
                find_paths(graph, p_current->column, dest_vertex, visited, path, path_index, found);
            }
            p_current = p_current->next;
        }
    }

    visited[current_vertex] = 0;
}