#include <stdio.h>
#include <stdlib.h>
#include "../include/leitos.h"

void inicializarLeitos(Leito leitos[]) {
    for (int i = 0; i < QTD_LEITOS; i++) {
        leitos[i].ocupado = NULL;
    }
}

int internarPaciente(Leito leitos[], Paciente p) {
    for (int i = 0; i < QTD_LEITOS; i++) {
        if (leitos[i].ocupado == NULL) {
            leitos[i].ocupado = (Paciente *)malloc(sizeof(Paciente));
            if (!leitos[i].ocupado) {
                perror("Erro ao alocar memória para paciente no leito");
                exit(EXIT_FAILURE);
            }
            *(leitos[i].ocupado) = p;
            return 1; // Internado com sucesso
        }
    }
    return 0; // Não há leitos disponíveis
}

int liberarLeito(Leito leitos[], int indice) {
    if (indice >= 0 && indice < QTD_LEITOS && leitos[indice].ocupado != NULL) {
        free(leitos[indice].ocupado);
        leitos[indice].ocupado = NULL;
        return 1;
    }
    return 0;
}

void mostrarLeitos(Leito leitos[]) {
    for (int i = 0; i < QTD_LEITOS; i++) {
        if (leitos[i].ocupado) {
            printf("Leito %d: %s (Prioridade %d)\n", i, leitos[i].ocupado->nome, leitos[i].ocupado->prioridade);
        } else {
            printf("Leito %d: Vazio\n", i);
        }
    }
}

void liberarTodosLeitos(Leito leitos[]) {
    for (int i = 0; i < QTD_LEITOS; i++) {
        if (leitos[i].ocupado != NULL) {
            free(leitos[i].ocupado);
            leitos[i].ocupado = NULL;
        }
    }
}
