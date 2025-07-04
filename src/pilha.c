#include <stdio.h>
#include <stdlib.h>
#include "../include/pilha.h"

void inicializarPilha(Pilha *p) {
    p->topo = NULL;
    p->tamanho = 0;
}

void empilharPaciente(Pilha *p, Paciente paciente) {
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    if (!novo) {
        perror("Erro ao alocar memória para pilha");
        exit(EXIT_FAILURE);
    }

    novo->paciente = paciente;
    novo->proximo = p->topo;
    p->topo = novo;
    p->tamanho++;
}

void mostrarPilha(Pilha *p) {
    NoPilha *atual = p->topo;
    printf("Pacientes com alta:\n");
    if (!atual) {
        printf("- Nenhum paciente com alta ainda.\n");
        return;
    }

    while (atual != NULL) {
        printf("- %s (Prioridade %d)\n", atual->paciente.nome, atual->paciente.prioridade);
        atual = atual->proximo;
    }
}

void liberarPilha(Pilha *p) {
    NoPilha *atual = p->topo;
    while (atual != NULL) {
        NoPilha *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    p->topo = NULL;
    p->tamanho = 0;
}
