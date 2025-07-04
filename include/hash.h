#ifndef HASH_H
#define HASH_H

#include "paciente.h"

#define TAM_MAX 53

typedef struct NoHash{ // Estrutura de um nó da tabela hash (representa a ficha de um paciente, que pode apontar para o próximo paciente caso eles tenham sido armazeandos na mesma posição da tabela hash)
    Paciente paciente;
    struct NoHash *proximo;
} NoHash;

typedef struct { // Estrutura da tabela hash, que é um vetor de ponteiros para NoHash
    NoHash *tabela[TAM_MAX];
}tabelaHash;

int funcaoHash(const char *id); // Função de hash que recebe o ID do paciente e retorna a posição na tabela hash
void inicializarHash(void);
void inserirHash(Paciente p); // Insere um paciente na tabela hash
Paciente *sortearPaciente(); // Sorteia um paciente da tabela hash, retornando um ponteiro para o paciente sorteado
void liberaHash();
int todosAtendidos(); // Verifica se todos os pacientes foram atendidos

#endif