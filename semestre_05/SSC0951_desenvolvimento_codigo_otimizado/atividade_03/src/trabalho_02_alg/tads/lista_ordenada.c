#include <stdio.h>
#include <stdlib.h>
#include "lista_ordenada.h"


/**
 * @void cria(ListaOrdenada *l);
 * - Estancia uma variável do tipo lista ordenada.
 */
void lo_criarListaOrdenada(void *lv) {
	ListaOrdenada *l  = (ListaOrdenada*) lv;
    l->ini = NULL;
    l->fim = NULL;
    return;
}

/**
 * @void lo_finalizarListaOrdenada(ListaOrdenada *l);
 * - Elimita a estância de uma Lista Ordenada.
 */
void lo_finalizarListaOrdenada(void *lv) {
    ListaOrdenada *l  = (ListaOrdenada*) lv;
    NoListaOrd *p;
    p = l->ini;
    
    while (l->ini != NULL) {
        l->ini = l->ini->prox;
        free(p);
        p = l->ini;
    }
    l->fim = NULL;
    return;
}

/**
 * @void cria(ListaOrdenada *l);
 * - Estancia uma variável do tipo lista ordenada.
 */
int lo_inserirElemento(void *lv, int x){
    
    // Criando o nó que irá ser inserido
    NoListaOrd *p;
    ListaOrdenada *l = (ListaOrdenada*) lv;
    
    
    p = (NoListaOrd *) malloc(sizeof(NoListaOrd));
    
    // Não há memória suficiente para alocar o valor
    if (p == NULL) return 1;
    
    // Atribuindo os valores
    p->info = x;
    p->prox = NULL;
    
    // Inserindo o nó na lista
    if (l->ini == NULL)
        l->ini = p;
    else
        l->fim->prox = p;
    l->fim = p;
    return 0;
}

/**
 * @void lo_printLista(ListaOrdenada l);
 * - Estancia uma variável do tipo lista ordenada.
 */
void lo_printLista(ListaOrdenada l){
    NoListaOrd *p;
    p = l.ini;
    while (p != NULL) {
        printf("%d ", p->info);
        p = p->prox;
    }
    printf("\n");
    return;
}

/**
 * @void lo_printLista(ListaOrdenada l);
 * - Busca um elemento na lista, retorna 1 caso encontra e 0 caso não.
 */
int lo_buscarElemento(void *lv, int x) {
	
	ListaOrdenada *l  = (ListaOrdenada*) lv;
	ListaOrdenada aux = *l;
	
    while (aux.ini != NULL) {
        if (aux.ini->info == x)
            return 1;
        aux.ini = aux.ini->prox;
    }
    return 0;
}

/**
 * @void lo_printLista(ListaOrdenada l);
 * - Procura o elemento x na lista, caso ele exista o elimina.
 */
int lo_eliminarElemento(void *lv, int x) {
	ListaOrdenada *l = (ListaOrdenada*) lv;
    NoListaOrd    *p, *ant;
    
    if (l->ini != NULL) {
        p = l->ini;
        ant = NULL;
        while (p != NULL) { // buscando
            if (p->info == x) { // achou
                if (p == l->ini)
                    l->ini = l->ini->prox; // elimina primeiro
                else
                    ant->prox = p->prox; // elimina outro
                if (p == l->fim)
                    l->fim = ant;
                free(p);
                return 0;
            }
            ant = p;
            p = p->prox;
        }
    }
    return 1; // nao achou
}


/**
 * @void lo_ordenarLista(ListaOrdenada *l);
 * - Ordena os elementos inseridos na lista
 */
void lo_troca_valores(NoListaOrd *i, NoListaOrd *j) {
    elem_LO aux;
    aux = i->info;
    i->info = j->info;
    j->info = aux;
    return;
}
void lo_ordenarLista(void *lv) {
    ListaOrdenada *l = (ListaOrdenada*) lv;
    NoListaOrd *i, *j;
    i = l->ini;
    while (i != l->fim) {
        j = i->prox;
        while (j != NULL) {
            if (i->info > j->info)
                lo_troca_valores(i, j);
            j = j->prox;
        }
        i = i->prox;
    }
    return;
}

