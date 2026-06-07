#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sparse-matrix/sparse_matrix.h"
#include "graph/graph.h"

void populate_sample_data(Graph *airline_network){
    register_airport(airline_network, "BSB", "Brasilia");
    register_airport(airline_network, "CNF", "Belo_Horizonte");
    register_airport(airline_network, "GIG", "Rio_de_Janeiro");
    register_airport(airline_network, "GRU", "Guarulhos");
    register_airport(airline_network, "SSA", "Salvador");

    register_flight(airline_network, 107, "BSB", "SSA");
    register_flight(airline_network, 555, "CNF", "GIG");
    register_flight(airline_network, 101, "CNF", "GRU");
    register_flight(airline_network, 214, "CNF", "SSA");
    register_flight(airline_network, 50, "GIG", "BSB");
    register_flight(airline_network, 554, "GIG", "CNF");
    register_flight(airline_network, 90, "GIG", "GRU");
    register_flight(airline_network, 102, "GRU", "CNF");
    register_flight(airline_network, 89, "GRU", "GIG");
    register_flight(airline_network, 215, "SSA", "GIG");
}

int main(){
    int opt = 0;
    int id = 0;
    char airport_initial_code[100];
    char airport_final_code[100];
    char buffer[100];
    char junk;
    Graph *airline_network = create_graph();

    populate_sample_data(airline_network);
    printf("Sample data loaded: 5 airports and 10 flights pre-registered.\n");

    while(opt != 6){
        printf("\nANAC AIR NETWORK SYSTEM\n");
        printf("\n [1] Register new Airport [2] Register flight [3] Remove flight [4] List flights [5] List possible routes [6] Exit program\n");
        printf("\n enter your option: ");
        
        if(scanf("%99s", buffer) != 1 || sscanf(buffer, "%d%c", &opt, &junk) != 1){
            printf("\n-> Invalid input! Please type a number between 1 and 6.\n");
            opt = 0;
            continue;
        }

        switch(opt){
            case 1:{
                char name[100], city[100];
                printf("Enter the airport name: ");
                scanf("%99s", name);
                printf("\nEnter the city: ");
                scanf("%99s", city);
                if(register_airport(airline_network, name, city) == 1){
                    printf("Airport registered!");
                }
                else{
                    printf("Error: Network is full!");
                }
                break;
            }
            case 2:{
                printf("Enter the flight ID (number): ");
                if(scanf("%99s", buffer) != 1 || sscanf(buffer, "%d%c", &id, &junk) != 1){
                    printf("\n-> Invalid input! Returning to menu.\n");
                    break;
                }

                while(check_flight_ID(airline_network, id) == 1){
                    printf("\n-> Error: This ID already exists!\n");
                    printf("\nEnter a different flight ID: ");
                    if(scanf("%99s", buffer) != 1 || sscanf(buffer, "%d%c", &id, &junk) != 1){
                        printf("\n-> Invalid input! Returning to menu.\n");
                        break;
                    }
                }

                if(check_flight_ID(airline_network, id) == 1){
                    break;
                }

                printf("Enter the Airport initial code: ");
                scanf("%99s", airport_initial_code);

                printf("Enter the Airport final code: ");
                scanf("%99s", airport_final_code);

                if(register_flight(airline_network, id, airport_initial_code, airport_final_code) == 1){
                    printf("\nFlight registered!\n");
                }
                else{
                    printf("\n-> Error: no Airport registered.");
                }
                break;
            }
            case 3:{
                printf("\nSelect the flight ID to remove: ");
                if(scanf("%99s", buffer) != 1 || sscanf(buffer, "%d%c", &id, &junk) != 1){
                    printf("\n-> Invalid input! Returning to menu.\n");
                    break;
                }
                if(remove_flight(airline_network, id) == 1){
                    printf("\nFlight Removed!\n");
                }
                else{
                    printf("\nError: no flight registered");
                }
                break;
            }
            case 4:
                list_flights(airline_network);
                break;
            case 5:{
                int visited[MAX];
                int start_index = -1;
                int final_index = -1;
                int path[MAX];
                int path_index = 0;

                for(int i = 0; i < MAX; i++){
                    visited[i] = 0;
                }

                printf("enter a Airport initial code: ");
                scanf("%99s", airport_initial_code);

                printf("enter a Airport final code: ");
                scanf("%99s", airport_final_code);

                for(int i = 0; i < airline_network->count; i++){
                    if(strcmp(airline_network->vertex[i].code_vertex, airport_initial_code) == 0){
                        start_index = i;
                    }
                    if(strcmp(airline_network->vertex[i].code_vertex, airport_final_code) == 0){
                        final_index = i;
                    }
                }

                if(start_index == -1 || final_index == -1){
                    printf("--> Error: empty space, try again!");
                }
                else{
                    int route_found = 0;
                    find_paths(airline_network, start_index, final_index, visited, path, path_index, &route_found);
                    if(route_found == 0){
                        printf("No route found");
                    }
                }
                break;
            }
            case 6:
                printf("\nExiting System...\n");
                break;
            default:
                printf("\n-> Invalid option! Please type a number between 1 and 6.\n");
        }
    }
}