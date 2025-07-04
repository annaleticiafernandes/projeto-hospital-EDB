#include <stdio.h>
#include <stdlib.h>
#include "../include/deque.h"

void inicializarDeque(Deque *d){
    d->inicio = NULL;
    d->fim = NULL;
    d->tamanho = 0;
}

void inserirDeque(Deque *d, Paciente p){
    NoDeque *novoNo = (NoDeque *)malloc(sizeof(NoDeque));
    novoNo->paciente = p;
    novoNo->proximo = NULL;
    novoNo->anterior = d->fim;

    if(d->fim != NULL){
        d->fim->proximo = novoNo;
    }
    d->fim = novoNo;

    if(d->inicio == NULL){
        d->inicio = novoNo;
    }
    d->tamanho++;
}

Paciente RemoverDeque(Deque *d){
    Paciente p;
    if(d->inicio == NULL){
        fprintf(stderr, "Deque vazio!\n");
        Paciente vazio = {0};
        return vazio;
    }

    NoDeque *remove = d->inicio;
    p = remove->paciente;
    d->inicio = remove->proximo;
    if(d->inicio != NULL){
        d->inicio->anterior = NULL;
    } else {
        d->fim = NULL; 
    }

    free(remove);
    d->tamanho--;  
    return p;
}

void liberarDeque(Deque *d){
    NoDeque *atual = d->inicio;
    while(atual != NULL){
        NoDeque *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    d->inicio = NULL;
    d->fim = NULL;
    d->tamanho = 0;
}