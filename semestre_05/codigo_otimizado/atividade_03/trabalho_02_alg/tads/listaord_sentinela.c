#include <stdlib.h>
#include <stdio.h>
#include "listaord_sentinela.h"

/**
 * @int los_criarLista(ListaOrdSent *l);
 * - Estancia uma variável do tipo lista ordenada Sentinela.
 */
void los_criarLista(void *lv) {
	ListaOrdSent *l = (ListaOrdSent*) lv; 
    l->sentinela = malloc(sizeof(NoLOS));
    if (l->sentinela == NULL)
        return; // erro
    l->sentinela->prox = NULL;
    l->ini = l->sentinela;
    return; // sucesso
}

/**
 * @void lo_finalizarListaOrdenada(ListaOrdenada *l);
 * - Elimita a estância de uma Lista Ordenada com Sentinela
 */
void los_finalizarLista(void *lv) {
	ListaOrdSent *l = (ListaOrdSent*) lv; 
    NoLOS *aux;
    while (l->ini != NULL) {
        aux = l->ini;
        l->ini = l->ini->prox;
        free(aux);
    }
    l->sentinela = NULL;
    return;
}

// Funcao auxiliar para as funcoes seguintes
void los_busca_interna(ListaOrdSent *l, elem_LOS x, NoLOS **ant, NoLOS **p) {
    l->sentinela->info = x;
    *ant = NULL;
    *p = l->ini;
    while ((*p)->info < x) {
        *ant = *p;
        *p = (*p)->prox;
    }
    return;
}

/**
 * @int los_inserirElemento(ListaOrdenada *l, elem_LO x);
 * - Insere um novo elemento na Lista Ordenada com Sentinela
 */
int los_inserirElemento(void *lv, int x) {
	ListaOrdSent *l = (ListaOrdSent*) lv; 
	NoLOS *novo, *ant, *p;
	
	// busca primeiro maior ou igual a x
    los_busca_interna(l, x, &ant, &p); 
	
	// erro, elemento repetido
    if (p != l->sentinela && p->info == x)
        return 1; 
    
    novo = (NoLOS *) malloc(sizeof(NoLOS));
    
     // erro, memoria insuficiente
    if (novo == NULL)
        return 1;
        
    novo->info = x; 
    novo->prox = p;
    
    if (ant == NULL) l->ini = novo; // insere no inicio
    else ant->prox = novo; // insere no meio ou fim
        
    return 0; // sucesso
}

/**
 * @int los_eliminarElemento(ListaOrdenada *l, elem_LOS x);
 * - Procura o elemento x na lista, caso ele exista o elimina.
 */	
int los_eliminarElemento(void *lv, int x) {
    ListaOrdSent *l = (ListaOrdSent*) lv; 
    NoLOS *ant, *p;
    
    los_busca_interna(l, x, &ant, &p);
    if (p == l->sentinela || p->info != x)
        return 1; // erro
    if (l->ini == p)
        l->ini = l->ini->prox; // remove do inicio
    else
        ant->prox = p->prox; // remove do meio ou do final
    free(p);
    return 0; // sucesso
}

/**
 * @int los_buscarElemento(ListaOrdenada l, elem_LOS x);
 * - Busca um elemento na lista, retorna 1 caso encontra e 0 caso não.
 */
int los_buscarElemento(void *lv, int x) {
	ListaOrdSent *l = (ListaOrdSent*) lv; 
	ListaOrdSent aux = *l;
	
    aux.sentinela->info = x;
    while(aux.ini->info < x)
        aux.ini = aux.ini->prox;
    return (aux.ini != aux.sentinela && aux.ini->info == x);
}

int los_esta_vazia(ListaOrdSent l) {
    return (l.ini == l.sentinela);
}
void los_imprime(ListaOrdSent l) {
    while (l.ini != l.sentinela) {
        printf("%d ", l.ini->info);
        l.ini = l.ini->prox;
    }
    printf("\n");
    return;
}

