#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#define MAX 100
typedef struct NodeMatrix {
    int column;

    struct NodeMatrix *next; //ponteiro que aponta para o proximo node da lista

    void *data; //guarda qualquer coisa que se deseje guardar com void
} NodeMatrix;

NodeMatrix **create_matrix(int size);

void add_data(NodeMatrix **sparse_matrix, void *data, int row, int column); //(**) vetor de ponteiros

int remove_data(NodeMatrix **sparse_matrix, int row, int column);

void free_matrix(NodeMatrix **sparse_matrix, int size);

#endif