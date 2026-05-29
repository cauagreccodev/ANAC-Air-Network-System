#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"

NodeMatrix **create_matrix(int size){
    NodeMatrix **p = malloc(size * sizeof(NodeMatrix *));
    for(int i = 0; i < size; i++){
        p[i] = NULL;
    }
    return p;
}

void add_data(NodeMatrix **sparse_matrix, void *data, int row, int column){
    NodeMatrix *p = malloc(sizeof(NodeMatrix));
    p->data = data;
    p->column = column;
    p->next = sparse_matrix[row];
    sparse_matrix[row] = p;
}

int remove_data(NodeMatrix **sparse_matrix, int row, int column){
    NodeMatrix *p_current = sparse_matrix[row];
    NodeMatrix *prev = NULL;
    while(p_current != NULL && p_current->column != column){
        prev = p_current;
        p_current = p_current->next;
    }
    if (p_current == NULL) {
        return 0; // Não achou a caixa
    }
    if (prev == NULL) { // se for o primeiro
        sparse_matrix[row] = p_current->next;
    }
    else{ //se estiver no meio ou no final
        prev->next = p_current->next; //segura o que esta na frente de p_current caso tenha algo
    }
    free(p_current);
    return 1;
}

void free_matrix(NodeMatrix **sparse_matrix,int size){
    for(int i = 0; i < size; i++){
        NodeMatrix *p_current = sparse_matrix[i];
        while (p_current != NULL){
            NodeMatrix *temp = p_current->next; //segura o proximo
            free(p_current);        //remove o atual 
            p_current = temp;       //caminha para frente
        }
    }
    free(sparse_matrix);
}