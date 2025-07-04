#ifndef PILHA_H
#define PILHA_H

#include "../include/paciente.h"

typedef struct NoPilha {
    Paciente paciente;
    struct NoPilha *proximo;
} NoPilha;

typedef struct {
    NoPilha *topo;
    int tamanho;
} Pilha;

void inicializarPilha(Pilha *p);
void empilharPaciente(Pilha *p, Paciente paciente);
void mostrarPilha(Pilha *p);
void liberarPilha(Pilha *p);

#endif
