#ifndef HASH_H
#define HASH_H

#include "paciente.h"

#define TAM_MAX 53

typedef struct NoHash{ 
    Paciente paciente;
    struct NoHash *proximo;
} NoHash;

typedef struct { 
    NoHash *tabela[TAM_MAX];
}tabelaHash;

int funcaoHash(const char *id); 
void inicializarHash(void);
void inserirHash(Paciente p); 
Paciente *sortearPaciente(); 
void liberaHash();
int todosAtendidos(); 

#endif