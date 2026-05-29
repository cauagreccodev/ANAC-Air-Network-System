#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sparse-matrix/sparse_matrix.h"
#include "graph/graph.h"

int main(){
    int opt = 0;
    int id = 0;
    char airport_initial_code[100];
    char airport_final_code[100];
    Graph *airline_network = create_graph();

    while(opt != 6){
        printf("\nANAC AIR NETWORK SYSTEM\n");
        printf("\n [1] Register new Airport [2] Register flight [3] Remove flight [4] List flights [5] List possible routes [6] Exit program\n");
        printf("\n enter your option: ");
        scanf("%d", &opt);

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
                scanf("%d", &id);

                while(check_flight_ID(airline_network, id) == 1){
                    printf("\n-> Error: This ID already exists!\n");
                    printf("\nEnter a different flight ID: ");
                    scanf("%d", &id);
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
                scanf("%d", &id);
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