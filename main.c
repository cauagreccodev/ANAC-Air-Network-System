#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sparse-matrix/sparse_matrix.h"
#include "graph/graph.h"

int main(){
    int opt = 0;
    Graph *airline_network = create_graph();
    while(opt != 6){
        printf("\nANAC AIR NETWORK SYSTEM\n");
        printf("\n [1] Register new Airport [2] Register flight [3] Remove flight [4] List flights [5] List possible routes [6] Exit program\n");
        printf("\n enter your option: ");
        scanf("%d",&opt);

        switch(opt){
            case 1:
                char name[100], city[100];
                printf("Enter the airport name: ");
                scanf("%s",name);
                printf("\nEnter the city: ");
                scanf("%s",city);
                if(register_airport(airline_network, name, city) == 1){
                    printf("Airport registered!");
                }
                else{
                    printf("Error: Network is full!");
                }
                break;
            case 2:
                int id;
                char airport_initial_code[100], airport_final_code[100];
                printf("Enter the flight ID (number): ");
                scanf("%d",&id);
                
                while(check_flight_ID != 0){
                    printf("\n-> Error: This ID already exists!\n");
                    printf("\nEnter a different flight ID: ");
                    scanf("%d",&id);
                }
                
                printf("Enter the airport_initial_code: ");
                scanf("%99s",&airport_initial_code); //evitar buff overflow com %99s e evitar usuario digitar vazio
                
                printf("Enter the airport_final_code: ");
                scanf("%99s",&airport_final_code);

                if(register_flight(airline_network, id, airport_initial_code, airport_final_code) == 1){
                    printf("\nFlight registered!\n");
                }
                else{
                    printf("\n-> Error: no Airport registered.");
                }
                break;
            case 3:
                printf("\nSelect the flight ID to remove: ");
                scanf("%d",&id);
                if(remove_flight(airline_network,id) == 1){
                    printf("\nFlight Removed!\n");
                }
                else{
                    printf("\nError: no flight registered");
                }
                break;
            case 4:
                list_flights(airline_network);
                break;
            case 6:
                printf("\nExiting System...\n");
                break;
            default:
                printf("\n-> Invalid option! Please type a number between 1 and 6.\n");
        }
    }
}