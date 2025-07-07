#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/hash.h"

NoHash *tabela[TAM_MAX]; // Tabela hash, que é um vetor de ponteiros para NoHash

void inicializarHash(void){
    for(int i = 0; i < TAM_MAX; i++) {
        tabela[i] = NULL; // Inicializa cada posição da tabela hash com NULL
    }
}

int funcaoHash(const char *id) { // Função que calcula o índice da tabela hash baseado no ID do paciente
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
        tabela[index] = novoNo; // Insere o novo nó se a posição estiver vazia
    } else {
        novoNo->proximo = tabela[index]; // Insere o novo nó no início da lista encadeada
        tabela[index] = novoNo;
    }
}

int todosAtendidos() {
    for (int i = 0; i < TAM_MAX; i++) {
        NoHash *atual = tabela[i];
        while (atual != NULL) {
            if (!atual->paciente.atendido) {
                return 0; // Retorna 0 se encontrar algum paciente não atendido
            }
            atual = atual->proximo;
        }
    }
    return 1; // Retorna 1 se todos os pacientes foram atendidos
}

void liberaHash() {
    for (int i = 0; i < TAM_MAX; i++) {
        NoHash *atual = tabela[i];
        while (atual != NULL) {
            NoHash *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
        tabela[i] = NULL; // Limpa a posição da tabela hash
    }
}

Paciente* sortearPaciente() {
    // Conta total de pacientes disponíveis
    int candidatos = 0;
    for (int i = 0; i < TAM_MAX; i++) {
        for (NoHash *atual = tabela[i]; atual != NULL; atual = atual->proximo) {
            if (atual->paciente.atendido == 0) {
                candidatos++;
            }
        }
    }

    if (candidatos == 0) return NULL;

    // Escolhe aleatoriamente entre os candidatos
    int alvo = rand() % candidatos;
    int cont = 0;

    for (int i = 0; i < TAM_MAX; i++) {
        NoHash **anterior = &tabela[i];
        NoHash *atual = tabela[i];

        while (atual != NULL) {
            if (atual->paciente.atendido == 0) {
                if (cont == alvo) {
                    atual->paciente.atendido = 1;

                    // Remove da hash
                    *anterior = atual->proximo;

                    // Copia para retorno
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