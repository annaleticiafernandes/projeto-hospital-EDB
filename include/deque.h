#ifndef DEQUE_H
#define DEQUE_H

#include "paciente.h"

#define CAPACIDADE_MAX 20

typedef struct NoDeque{
    Paciente paciente;
    struct NoDeque *anterior;
    struct NoDeque *proximo;
} NoDeque;

typedef struct {
    NoDeque *inicio;
    NoDeque *fim;
    int tamanho;
} Deque;

void inicializarDeque(Deque *d);
void inserirDeque(Deque *d, Paciente p);
Paciente RemoverDeque(Deque *d);
void liberarDeque(Deque *d);

#endif