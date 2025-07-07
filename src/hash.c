#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hash.h"

NoHash *tabela[TAM_MAX]; 

void inicializarHash(void){
    for(int i = 0; i < TAM_MAX; i++) {
        tabela[i] = NULL; 
    }
}

int funcaoHash(const char *id) { 
    int soma = 0;
    for (int i = 0; id[i] != '\0'; i++) {
        soma += id[i];
    }
    return soma % TAM_MAX;
}

void inserirHash(Paciente p){
    int index = funcaoHash(p.id);

    NoHash *novoNo = (NoHash *)malloc(sizeof(NoHash));
    if (novoNo == NULL) {
        perror("Erro ao alocar memória para novo nó");
        return;
    }

    novoNo->paciente = p;
    novoNo->proximo = NULL;

    if(tabela[index] == NULL) {
        tabela[index] = novoNo; 
    } else {
        novoNo->proximo = tabela[index]; 
        tabela[index] = novoNo;
    }
}

int todosAtendidos() {
    for (int i = 0; i < TAM_MAX; i++) {
        NoHash *atual = tabela[i];
        while (atual != NULL) {
            if (!atual->paciente.atendido) {
                return 0; 
            }
            atual = atual->proximo;
        }
    }
    return 1; 
}

void liberaHash() {
    for (int i = 0; i < TAM_MAX; i++) {
        NoHash *atual = tabela[i];
        while (atual != NULL) {
            NoHash *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        tabela[i] = NULL; 
    }
}

Paciente* sortearPaciente() {
    int candidatos = 0;
    for (int i = 0; i < TAM_MAX; i++) {
        for (NoHash *atual = tabela[i]; atual != NULL; atual = atual->proximo) {
            if (atual->paciente.atendido == 0) {
                candidatos++;
            }
        }
    }

    if (candidatos == 0) return NULL;

    int alvo = rand() % candidatos;
    int cont = 0;

    for (int i = 0; i < TAM_MAX; i++) {
        NoHash **anterior = &tabela[i];
        NoHash *atual = tabela[i];

        while (atual != NULL) {
            if (atual->paciente.atendido == 0) {
                if (cont == alvo) {
                    atual->paciente.atendido = 1;

                    *anterior = atual->proximo;

                    Paciente *resultado = malloc(sizeof(Paciente));
                    if (!resultado) {
                        perror("Erro ao alocar paciente sorteado");
                        exit(EXIT_FAILURE);
                    }

                    *resultado = atual->paciente;
                    free(atual);
                    return resultado;
                }
                cont++;
            }

            anterior = &atual->proximo;
            atual = atual->proximo;
        }
    }

    return NULL;
}