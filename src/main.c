#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 
#include "../include/paciente.h"
#include "../include/hash.h"
#include "../include/deque.h"
#include "../include/leitos.h"
#include "../include/pilha.h"
#include "../include/log.h" 

int main() {
    srand(time(NULL));

    Paciente pacientes[100];
    int total = 0;
    lerCvs("pacientes.csv", pacientes, &total);
    printf("\nTotal de pacientes lidos: %d\n", total);

    inicializarHash();
    for (int i = 0; i < total; i++) {
        inserirHash(pacientes[i]);
    }

    Deque fila;
    inicializarDeque(&fila);

    Leito leitos[QTD_LEITOS];
    inicializarLeitos(leitos);

    Pilha pilhaAlta;
    inicializarPilha(&pilhaAlta);

    iniciarLog();

    int ciclo = 1;
    while (!todosAtendidos()) {
        logCiclo(ciclo); 
        printf("\n--- Ciclo %d ---\n", ciclo++);

        Paciente *sorteado = sortearPaciente();
        if (sorteado != NULL) {
            inserirDeque(&fila, *sorteado);
            logEspera(sorteado); 
            free(sorteado);
        }

        if (fila.tamanho > 0) {
            Paciente p = RemoverDeque(&fila);
            if (internarPaciente(leitos, p)) {
                logInternado(&p); 
            } else {
                inserirDeque(&fila, p);
            }
        }

        int indiceAlta = rand() % QTD_LEITOS;
        if (leitos[indiceAlta].ocupado != NULL) {
            Paciente p = *(leitos[indiceAlta].ocupado);
            empilharPaciente(&pilhaAlta, p);
            liberarLeito(leitos, indiceAlta);
            logAlta(&p); 
        }

        mostrarLeitos(leitos);

        sleep(2);
    }

    printf("\nTodos os pacientes foram atendidos.\n\n");
    mostrarPilha(&pilhaAlta);

    finalizarLog(); 
    liberarDeque(&fila);
    liberarTodosLeitos(leitos);
    liberaHash();
    liberarPilha(&pilhaAlta);

    return 0;
}
