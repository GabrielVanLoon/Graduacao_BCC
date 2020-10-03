#include <stdio.h>
#include <stdlib.h>
#include "listacirc_freq.h"

/**
 * @void cria(ListaOrdenada *l);
 * - Estancia uma variável do tipo lista ordenada.
 */
void lfreq_criarLista(void *lv){
    ListaFreq *l = (ListaFreq*) lv;
    l->ini = NULL;
    l->fim = NULL;
}

/**
 * @void lfreq_eliminarLista(void *lv);
 * - Elimina a estância de uma Lista de Frequencia
 */
void lfreq_eliminarLista(void *lv) {
    ListaFreq *l = (ListaFreq*) lv;
    NoLFREQ   *p = l->ini;
    NoLFREQ   *aux;

    if(l->ini == NULL) return;

    while (p != l->fim) {
        aux = p;
        p   = p->prox;
        free(aux);
    } free(p);
    return;
}

/**
 * @int lfreq_inserirElemento(void *lv, int x);
 * - Insere um novo elemento no final da Lista de Frequencia
 */
int lfreq_inserirElemento(void *lv, int x) {
    ListaFreq *l = (ListaFreq*) lv;
    NoLFREQ *p = (NoLFREQ *) malloc(sizeof(NoLFREQ));
   
    if (p == NULL)
        return 1; // erro

    p->info  = x; // copia info
    p->busca = 0;

    // atualiza encadeamento
    if (l->ini == NULL) { // Caso de lista vazia
        p->prox = p;
        p->ant  = p;
        l->ini  = p;
        l->fim  = p;
    } else { // insere no meio
        p->prox = l->ini;
        p->ant  = l->fim;
        l->ini->ant  = p;
        l->fim->prox = p;
        l->fim = p;
    }

    return 0; // sucesso
}

/**
* @int lo_eliminarElemento(ListaOrdenada *l, elem_LO x);
*/ 
int lfreq_eliminarElemento(void *lv, int x){
    ListaFreq *l = (ListaFreq*) lv;
    NoLFREQ *p   = l->ini;
    NoLFREQ *aux;

    // Caso a lista esteja vazia
    if(l->ini == NULL) return 1;

    // Percorrendo até achar o elemento
    while(p != l->fim && p->info != x){
        p = p->prox;
    }

    // Chegou no final e não achou o elemento
    if(p == l->fim && p->info != x) 
        return 1;

    // Caso só haja 1 elemento
    if(p->prox == p){
        l->ini = NULL;
        l->fim = NULL;
        free(p);
    } else {
        p->ant->prox = p->prox;
        p->prox->ant = p->ant;

        if(p == l->ini) l->ini = p->prox;
        if(p == l->fim) l->fim = p->ant;
        free(p);
    }

    return 0;
}

/**
 * @int lo_buscarElemento(ListaOrdenada *l, elem_LO x);
 * - Procura o elemento x na lista. Retorna 1 caso exista.
 */ 
int lfreq_buscarElemento(void *lv, int x){
    ListaFreq *l = (ListaFreq*) lv;
    NoLFREQ *p   = l->ini;
    
    elem_LFREQ  auxInfo;
    int         auxBusca;

    // Caso a lista esteja vazia
    if(l->ini == NULL) return 0;

    // Percorrendo até achar o elemento
    while(p != l->fim && p->info != x){
        p = p->prox;
    }

    // Chegou no final e não achou o elemento
    if(p->info != x)
        return 0;
    
    // Achou o elemento, ajusta o fator de busca dele
    if(p != l->ini){
        auxInfo  = p->info;
        auxBusca = p->busca;

        p->info  = p->ant->info;
        p->busca = p->ant->busca;

        p->ant->info  = auxInfo;
        p->ant->busca = auxBusca + 1;
    } else {
        p->busca += 1;
    }

    return 1;
}

/**
 * @void lfreq_printLista(void *lv);
 */ 
void lfreq_printLista(void *lv){
    ListaFreq *l = (ListaFreq*) lv;
    NoLFREQ   *p = l->ini;

    while(p != l->fim){
        printf("%d ", p->info);
        p = p->prox;
    }

    printf("%d\n", p->info);

    return;
}