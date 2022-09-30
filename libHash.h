#include <stdio.h>
#include <stdlib.h>

#ifndef __LIBHASH__
#define __LIBHASH__

typedef struct {
    int chave;
    int removido;
} no;

typedef struct {
    int chave;
    int tabela;
    int posicao;
} ordenador;

void iniciaTabela(no *tabela, int tamTab);

no criaNo(int chave);

void insere(no *t1, no *t2, int chave, int tamTab);

int busca(no *t1, no *t2, int chave, int tamTab, int *posicao, int *tabela);

void removeChave(no *t1, no *t2, int posicao, int tabela);

void imprimeTabelas(no *tab1, no *tab2, int aux);

#endif