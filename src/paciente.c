#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/paciente.h"

void lerCvs(const char *arquivo, Paciente pacientes[], int *total) {
    FILE *file = fopen(arquivo, "r");
    if (file == NULL){
        perror("Erro ao abrir o arquivo CSV");
        return;
    }

    char linha[256];
    *total = 0;

    while (fgets(linha, sizeof(linha), file)){
        if(*total == 0 && linha[0] == 'I'){
            continue;
        }

        sscanf(linha, "%[^;];%[^;];%d;%c;%[^;];%d;%d",
               pacientes[*total].id,
               pacientes[*total].nome,
               &pacientes[*total].idade,
               &pacientes[*total].sexo,
               pacientes[*total].cpf,
               &pacientes[*total].prioridade,
               &pacientes[*total].atendido);

        (*total)++;

        if (*total >= 100) { 
            break;
        }
    }

    fclose(file);
}