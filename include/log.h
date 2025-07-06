#ifndef LOG_H
#define LOG_H

#include "paciente.h"

void iniciarLog();
void finalizarLog();
void logCiclo(int ciclo);
void logAlta(Paciente *p);
void logInternado(Paciente *p);
void logEspera(Paciente *p);

#endif
