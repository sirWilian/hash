#include "libHash.h"
#include "math.h"

no criaNo(int chave){
    no item;

    item.chave = chave;
    item.removido = 0;

    return item; 
}

void iniciaTabela(no *tabela, int tamTab){
    for(int i = 0; i < tamTab; i++){
        tabela[i].removido = -1;
        tabela[i].chave = -3198;
    }
}

/* retorna posicao da chave em t2 */
int buscaTab2(no *tab, int chave, int tamTab, int *posicao){
    int index;

    index = floor(tamTab * (chave * 0.9 - floor(chave * 0.9)));
    if(tab[index].chave == chave){
        *posicao = index;
        return 1;
    }
    return 0;

}
int busca(no *t1, no *t2, int chave, int tamTab, int *posicao, int *tabela){
    int index;

    index = chave % tamTab;

    /* se removido == -1 significa que a chave está vazia  */
    if(t1[index].removido == -1)
        return 0;

    if(t1[index].removido == 0 || t1[index].removido == 1){
        /* caso exista em t1 */
        if(t1[index].removido == 0){
            if(t1[index].chave == chave){
                *posicao = index;
                *tabela = 1;
                return 1;
            }
        }
        if(buscaTab2(t2, chave, tamTab, posicao)){
            *tabela = 2;
            return 1;
        }
    }
    return 0;
}

int insereTabela2(no *tabela, no *item, int tamTab){
    int index;

    index = floor(tamTab * (item->chave * 0.9 - floor(item->chave * 0.9)));
    tabela[index] = *item;

    if(tabela[index].removido == 0)
        return 1;
    return 0;
}

int insereTabela1(no *tabela, no *tabela2, no *item, int tamTab){
    int index;
    no aux;

    /* calcula a posicao na tabela 1 */
    index = (item->chave % tamTab);
    if(index >= tamTab){
        fprintf(stderr, "index maior que tamanho da tabela");
        exit(1);
    }
    if(tabela[index].removido == 0){
        aux = criaNo(tabela[index].chave);
        insereTabela2(tabela2, &aux, tamTab);
    }

    tabela[index] = *item;

    if(tabela[index].removido == 0)
        return 1;
    return 0;
}

void insere(no *t1, no *t2, int chave, int tamTab){
    no item;
    int posicao = 0;
    int tabela = 0;

    /* se a chave já existe, não faz nada */
    if(busca(t1, t2, chave, tamTab, &posicao, &tabela))
        return;

    item = criaNo(chave);

    /* tenta inserir na tabela 1 */
    if(insereTabela1(t1, t2, &item, tamTab))
        return;
    /* tenta inserir na tabela 2 */
    if(insereTabela2(t2, &item, tamTab))
        return;

    fprintf(stderr, "erro ao inserir chave!");
}

void removeChave(no *t1, no *t2, int posicao, int tabela){
    if(tabela == 1){
        t1[posicao].chave = 0;
        t1[posicao].removido = 1;
        return;
    }
    t2[posicao].chave = 0;
    t2[posicao].removido = 1;
}
/* funcoes usadas para ordenar e imprimir um vetor que une as duas tabelas */
void troca(ordenador vetor[], int a, int b){
        float x;
        int pos;
        int tabela;

        x = vetor[a].chave;
        pos = vetor[a].posicao;
        tabela = vetor[a].tabela;

        vetor[a].chave = vetor[b].chave;
        vetor[a].posicao = vetor[b].posicao;
        vetor[a].tabela = vetor[b].tabela;
        
        vetor[b].chave = x;
        vetor[b].posicao = pos;
        vetor[b].tabela = tabela;
}

int particiona(ordenador v[], int a, int b, float valor, int *numComp){
    int m = a -1;
    int i;
    for(i=a; i<=b; i++) {
        (*numComp)++;
        if(v[i].chave <= valor) {
            m++;
            troca(v, m, i);
        }
    }   
    return m;
}

int quickSort2(ordenador vetor[], int a, int b){
    if(a >= b)
        return 0;
    int m; 
    int numComp = 0;
    m = particiona(vetor, a, b, vetor[b].chave, &numComp);
    return numComp + quickSort2(vetor, a, m-1) + quickSort2(vetor, m+1, b);
}

int quickSort(ordenador vetor[], int tam){
    return quickSort2(vetor, 0, tam-1);
}

void imprimeTabelas(no *tab1, no *tab2, int aux){
    ordenador *vetor;
    int i, j;

    /* une as tabelas */
    if(!(vetor = malloc(sizeof(ordenador)*aux))){
        fprintf(stderr, "erro de alocação no vetor de ordenacao");
        exit(1);
    }

    for(i = 0; i < (aux/2); i++){
        vetor[i].chave = tab1[i].chave;
        vetor[i].posicao = i;
        vetor[i].tabela = 1;
    }
    j = 0;

    for(i++; i < aux; i++){
        vetor[i].chave = tab2[j].chave;
        vetor[i].posicao = j;
        vetor[i].tabela = 2;
        j++;
    }
    /* ordena o vetor */
    quickSort(vetor, aux);

    /* imprime as tabelas */
    for(i = 0; i < aux; i++){
        if(vetor[i].tabela == 1)
            if(tab1[vetor[i].posicao].removido == 0)
                printf("%d,T1,%d\n", vetor[i].chave, vetor[i].posicao);
        if(vetor[i].tabela == 2)
            if(tab2[vetor[i].posicao].removido == 0)
                printf("%d,T2,%d\n", vetor[i].chave, vetor[i].posicao);            
    }
    free(vetor);
}