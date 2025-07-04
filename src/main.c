#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/paciente.h"
#include "../include/hash.h"
#include "../include/deque.h"
#include "../include/leitos.h"
#include "../include/pilha.h"

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

    // Loop de simulação
    int ciclo = 1;
    while (!todosAtendidos()) {
        printf("\n--- Ciclo %d ---\n", ciclo++);

        // Sorteia paciente da hash
        Paciente *sorteado = sortearPaciente();
        if (sorteado != NULL) {
            printf("Sorteado: %s (prioridade %d)\n", sorteado->nome, sorteado->prioridade);
            inserirDeque(&fila, *sorteado);
            free(sorteado);
        } else {
            printf("Nenhum paciente sorteado.\n");
        }

        // Remove do deque e tenta internar
        if (fila.tamanho > 0) {
            Paciente p = RemoverDeque(&fila);
            if (internarPaciente(leitos, p)) {
                printf("Paciente %s internado.\n", p.nome);
            } else {
                printf("Sem leitos disponíveis para %s. Voltando para a fila.\n", p.nome);
                inserirDeque(&fila, p); // Reinsere na fila
            }
        }

        // Simula alta (um leito aleatório)
        int indiceAlta = rand() % QTD_LEITOS;
        if (leitos[indiceAlta].ocupado != NULL) {
            Paciente p = *(leitos[indiceAlta].ocupado);
            empilharPaciente(&pilhaAlta, p);
            liberarLeito(leitos, indiceAlta);
            printf("Alta: %s (Leito %d)\n", p.nome, indiceAlta);
        }

        // Mostrar estado atual
        mostrarLeitos(leitos);
        printf("\n");
    }

    // Finalização
    printf("\nTodos os pacientes foram atendidos.\n\n");
    mostrarPilha(&pilhaAlta);

    // Liberação de memória
    liberarDeque(&fila);
    liberarTodosLeitos(leitos);
    liberaHash();
    liberarPilha(&pilhaAlta);

    return 0;
}
