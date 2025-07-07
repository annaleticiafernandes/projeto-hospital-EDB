#ifndef LEITOS_H
#define LEITOS_H

#include "../include/paciente.h"

#define QTD_LEITOS 5

typedef struct {
    Paciente *ocupado; 
} Leito;

void inicializarLeitos(Leito leitos[]);
int internarPaciente(Leito leitos[], Paciente p); 
int liberarLeito(Leito leitos[], int indice);    
void mostrarLeitos(Leito leitos[]);
void liberarTodosLeitos(Leito leitos[]);

#endif
