#include "libHash.h"
#define M 11

int main(){
    char operacao;
    int chave, index, tabela;
    no *tab1, *tab2;
    
    if(!(tab1 = malloc(sizeof(no) * M))){
        fprintf(stderr, "erro de alocacao na tabela 1");
        exit(1);
    }
    if(!(tab2 = malloc(sizeof(no) * M))){
        fprintf(stderr, "erro de alocacao na tabela 2");
        exit(1);
    }

    index = tabela = 0;
    iniciaTabela(tab1, M);
    iniciaTabela(tab2, M);

    operacao = getchar();
    while(operacao != EOF){
        scanf("%d", &chave);
        if(operacao == 'i') 
            insere(tab1, tab2, chave, M);
        if(operacao == 'r'){
            if(busca(tab1, tab2, chave, M, &index, &tabela)) 
                removeChave(tab1, tab2, index, tabela);
        }
        operacao = getchar();
    }

    imprimeTabelas(tab1, tab2, 2*M);

    free(tab1);
    free(tab2);

    return 0;
}