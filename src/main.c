#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/paciente.h"
#include "../include/hash.h"

int main() {
    Paciente pacientes[TAM_MAX];
    int total = 0;

    lerCvs("pacientes.csv", pacientes, &total);
    printf("Lidos %d pacientes\n", total);

    for (int i = 0; i < total; i++) {
        inserirHash(pacientes[i]);
    }

    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        Paciente *p = sortearPaciente();
        if (p) {
            printf("Sorteado: %s (%s) prioridade %d\n", p->id, p->nome, p->prioridade);
            free(p);
        } else {
            printf("Todos os pacientes já foram sorteados.\n");
        }
    }

    liberaHash();
    return 0;
}
