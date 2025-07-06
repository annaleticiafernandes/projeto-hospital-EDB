#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Para sleep()
#include "../include/paciente.h"
#include "../include/hash.h"
#include "../include/deque.h"
#include "../include/leitos.h"
#include "../include/pilha.h"
#include "../include/log.h" // NOVO: módulo de log

int main() {
    srand(time(NULL));

    // Etapa 1: Carregar pacientes do CSV
    Paciente pacientes[100];
    int total = 0;
    lerCvs("pacientes.csv", pacientes, &total);
    printf("\nTotal de pacientes lidos: %d\n", total);

    // Etapa 2: Inicializar estruturas
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

    // Inicializar log
    iniciarLog();

    // Loop de simulação
    int ciclo = 1;
    while (!todosAtendidos()) {
        logCiclo(ciclo); // Log do início do ciclo
        printf("\n--- Ciclo %d ---\n", ciclo++);

        // Sorteia paciente da hash
        Paciente *sorteado = sortearPaciente();
        if (sorteado != NULL) {
            inserirDeque(&fila, *sorteado);
            logEspera(sorteado); // Log de espera
            free(sorteado);
        }

        // Remove do deque e tenta internar
        if (fila.tamanho > 0) {
            Paciente p = RemoverDeque(&fila);
            if (internarPaciente(leitos, p)) {
                logInternado(&p); // Log de internado
            } else {
                inserirDeque(&fila, p); // Reinsere na fila
            }
        }

        // Simula alta (um leito aleatório)
        int indiceAlta = rand() % QTD_LEITOS;
        if (leitos[indiceAlta].ocupado != NULL) {
            Paciente p = *(leitos[indiceAlta].ocupado);
            empilharPaciente(&pilhaAlta, p);
            liberarLeito(leitos, indiceAlta);
            logAlta(&p); // Log de alta
        }

        // Mostrar estado atual
        mostrarLeitos(leitos);

        sleep(2); // Espera 2 segundos entre ciclos
    }

    printf("\nTodos os pacientes foram atendidos.\n\n");
    mostrarPilha(&pilhaAlta);

    // Finalização
    finalizarLog(); // Fecha o arquivo de log
    liberarDeque(&fila);
    liberarTodosLeitos(leitos);
    liberaHash();
    liberarPilha(&pilhaAlta);

    return 0;
}
