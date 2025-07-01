#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
    char id[10];
    char nome[50];
    int idade;
    char sexo;
    char cpf[15];
    int prioridade;
    int atendido;
} Paciente;

void lerCvs(const char *arquivo, Paciente pacientes[], int *total);

#endif
