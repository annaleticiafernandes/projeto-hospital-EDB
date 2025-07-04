#ifndef LEITOS_H
#define LEITOS_H

#include "../include/paciente.h"

#define QTD_LEITOS 5

typedef struct {
    Paciente *ocupado; // Ponteiro para paciente internado
} Leito;

void inicializarLeitos(Leito leitos[]);
int internarPaciente(Leito leitos[], Paciente p); // Retorna 1 se conseguiu internar
int liberarLeito(Leito leitos[], int indice);     // Retorna 1 se liberou com sucesso
void mostrarLeitos(Leito leitos[]);
void liberarTodosLeitos(Leito leitos[]);

#endif
