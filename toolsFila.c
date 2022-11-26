#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "estrutura.h"

// Cria uma cache no tipo lista vazia
void FLVazia (TipoLista *Lista){
    Lista -> Primeiro = (Celula*) malloc(sizeof(Celula));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
    Lista -> Tamanho = 0;
}

// Verifica se a Cache esta vazia
int Vazia (TipoLista Lista){
    return (Lista.Primeiro == Lista.Ultimo);
}

//Insere no fim da lista
void Insere (LinhaCache novaLinha, TipoLista *Lista){
    Lista -> Ultimo -> Prox = (Celula*) malloc(sizeof(Celula));
    Lista -> Ultimo = Lista -> Ultimo -> Prox;
    Lista -> Ultimo -> Linha = novaLinha;
    Lista -> Ultimo -> Prox = NULL;
    Lista -> Tamanho++;
}

// Busca um valor na lista remove caso encontre
void Retira (Celula* p, TipoLista *Lista){
    Celula* q;
    if (Vazia(*Lista)){
        printf ("Erro: cache vazia ou posicao inexistente.\n");
    }else if(p->Prox==NULL){
        q = Lista->Primeiro;
        while(q->Prox != p){
            q = q->Prox;
        }
        q->Prox = NULL;
        Lista->Ultimo = q;
        Lista->Tamanho--;
        free(p);
    }else{
        q = p->Prox;
        p->Prox = q->Prox;
        if (p->Prox == NULL)
            Lista->Ultimo = p;
        free(q);
        Lista->Tamanho--;
    }
}

// Busca um valor na lista remove caso encontre
void RetiraPrimeiro (Celula* p, TipoLista *Lista){
    if (Vazia(*Lista)){
        printf ("Erro: cache vazia ou posicao inexistente.\n");
    }else if(p->Prox==NULL){
        Lista -> Primeiro = (Celula*) malloc(sizeof(Celula));
        Lista -> Ultimo = Lista -> Primeiro;
        Lista -> Primeiro -> Prox = NULL;
        Lista->Tamanho--;
        free(p);
    }else{
        Lista->Primeiro = p->Prox;
        Lista->Tamanho--;
        free(p);
    }
}

// Imprime uma lista
void Imprime(TipoLista Lista){
    Celula* Aux;
    Aux = Lista.Primeiro -> Prox;
    printf ("\n-----------------------------------------------------");
    while (Aux != NULL){
        printf ("\nValor 1 => %d - posicao na PRINCIPAL => %d", Aux->Linha.valor1, Aux->Linha.posicaoValor1);
        printf ("\nValor 2 => %d - posicao na PRINCIPAL => %d", Aux->Linha.valor2, Aux->Linha.posicaoValor2);
        printf ("\nAlteracao: %d", Aux->Linha.alteracao);
        printf ("\nMESI: %c", Aux->Linha.mesi);
        printf ("\n-----------------------------------------------------");
        Aux=Aux->Prox;
    }
}

// Imprime uma Celula
void ImprimeCelula(Celula cel){
    printf("\n> Celula -----------------------------------");
    printf ("\nvalor1: %d", cel.Linha.valor1);
    printf ("\nvalor2: %d", cel.Linha.valor2);
    printf ("\nverificador de alteracao: %d", cel.Linha.alteracao);
    printf ("\nFIFO: %d", cel.Linha.fifo);
    printf ("\nMESI: %c", cel.Linha.mesi);
    printf ("\n-----------------------------------------------------\n");
}

// Imprime caches
void ImprimeCaches(int p, TipoLista *memCache, TipoLista *memCacheAux1, TipoLista *memCacheAux2){
    if(p == 1){
        printf("\n---> Cache do processador %d\n", p);
        Imprime(*memCache);
        printf("\n---> Cache do processador %d\n", 2);
        Imprime(*memCacheAux1);
        printf("\n---> Cache do processador %d\n", 3);
        Imprime(*memCacheAux2);
    }else if(p == 2){
        printf("\n---> Cache do processador %d\n", 1);
        Imprime(*memCacheAux1);
        printf("\n---> Cache do processador %d\n", p);
        Imprime(*memCache);
        printf("\n---> Cache do processador %d\n", 3);
        Imprime(*memCacheAux2);
    }else{
        printf("\n---> Cache do processador %d\n", 1);
        Imprime(*memCacheAux1);
        printf("\n---> Cache do processador %d\n", 2);
        Imprime(*memCacheAux2);
        printf("\n---> Cache do processador %d\n", p);
        Imprime(*memCache);
    }
}