#include "log.h"
#include <stdio.h>
#include <stdlib.h>

static FILE *arquivoLog = NULL;

void iniciarLog() {
    arquivoLog = fopen("processamento.log", "w");
    if (arquivoLog == NULL) {
        perror("Erro ao criar processamento.log");
        exit(1);
    }
}

void finalizarLog() {
    if (arquivoLog != NULL) {
        fclose(arquivoLog);
        arquivoLog = NULL;
    }
}

void logCiclo(int ciclo) {
    printf("\n[CICLO %02d]\n", ciclo);
    fprintf(arquivoLog, "\n[CICLO %02d]\n", ciclo);
}

void logAlta(Paciente *p) {
    printf("ALTA - %s (%s)\n", p->id, p->nome);
    fprintf(arquivoLog, "ALTA - %s (%s)\n", p->id, p->nome);
}

void logInternado(Paciente *p) {
    printf("INTERNADO - %s (prioridade %d)\n", p->id, p->prioridade);
    fprintf(arquivoLog, "INTERNADO - %s (prioridade %d)\n", p->id, p->prioridade);
}

void logEspera(Paciente *p) {
    printf("ESPERA - %s (prioridade %d)\n", p->id, p->prioridade);
    fprintf(arquivoLog, "ESPERA - %s (prioridade %d)\n", p->id, p->prioridade);
}
