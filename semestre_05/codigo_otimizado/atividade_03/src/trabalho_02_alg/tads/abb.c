#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

/**
 * @void abb_criarArvore(ABB *a);
 * - Estancia uma variável do Arvore de Busca Binaria
 */
void abb_criarArvore(void *av) {
	ABB *a = (ABB*) av;
    a->raiz = NULL;
    return;
}

/**
 * @void lo_finalizarListaOrdenada(ListaOrdenada *l);
 * - Elimina a estância de uma Arvore de Busca Binária
 */
void abb_destroiSub(NoABB *p) {
    if (p == NULL)
        return;
    abb_destroiSub(p->esq); // destroi subarvore esquerda
    abb_destroiSub(p->dir); // destroi subarvore direita
    free(p); // apaga o raiz da subarvore
    return;
}
void abb_eliminarArvore(void *av) {
	ABB *a = (ABB*) av;
    abb_destroiSub(a->raiz); // inicia recursao
    a->raiz = NULL;
    return;
}

/**
 * @int abb_estaVazia(ABB a);
 * - Retorna se uma arvore está ou não vazia
 */
int abb_estaVazia(ABB a) {
    return a.raiz == NULL;
}

/**
 * @void abb_printArvore(ABB a);
 * - Realiza o print dos elementos de uma arvore
 */
void abb_imprimeSub(NoABB *p) {
    printf("{");
    if (p != NULL) {
        printf("%d, ", p->info);
        abb_imprimeSub(p->esq);
        printf(", ");
        abb_imprimeSub(p->dir);
    }
    printf("}");
    return;
}
void abb_printArvore(ABB a) {
    abb_imprimeSub(a.raiz);
    printf("\n");
    return;
}

/**
 * @int abb_buscarElemento(ABB a, elem_ABB x);
 * - Busca um elemento na arvore, retorna 1 caso encontra e 0 caso não.
 */
int abb_buscaSub(NoABB *p, elem_ABB x) {
    if (p == NULL)
        return 0; // nao achou
    if (p->info == x)
        return 1; // achou
       
    return (x < p->info) ? abb_buscaSub(p->esq, x) : abb_buscaSub(p->dir, x);
}
int abb_buscarElemento(void *av, int x) {
	ABB *a = (ABB*) av;
    return abb_buscaSub(a->raiz, x); // inicia recursao
}

// Auxiliar para as funcoes seguintes
NoABB* abb_criaNo(elem_ABB info, NoABB *esq, NoABB *dir) {
    NoABB *nova = malloc(sizeof(NoABB));
    if (nova != NULL) {
        nova->info = info;
        nova->esq = esq;
        nova->dir = dir;
    }
    return nova;
}

/**
 * @int abb_buscarElemento(ABB a, elem_ABB x);
 * - Busca um elemento na arvore, retorna 1 caso encontra e 0 caso não.
 */
int abb_insercaoSub(NoABB **p, elem_ABB x) {
    // p => No **; *p => No *; **p => No
    if (*p == NULL) {
        *p = abb_criaNo(x, NULL, NULL); // insere
        return *p == NULL; // erro de memoria ou sucesso
    }
    if ((*p)->info == x)
        return 1; // erro, achou
    return (x < (*p)->info) ? abb_insercaoSub(&((*p)->esq), x) : abb_insercaoSub(&((*p)->dir), x);
}
int abb_inserirElemento(void *av, int x) {
	ABB *a = (ABB*) av;
    return abb_insercaoSub(&(a->raiz), x); // inicia recursao
}

/**
 * @int abb_eliminarElemento(ABB *a, elem_ABB x);
 * - Busca um elemento na arvore, remove ele caso ele exista.
 */
int abb_remocaoSub(NoABB **p, elem_ABB x) {
    // p => No **; *p => No *; **p => No
    int numFilhos = 0;
    NoABB *aux, *paiAux;
    if (*p == NULL)
        return 1; // erro, elemento nao existe
    if ((*p)->info == x) { // achou, entao remove
        if ((*p)->esq != NULL)
            numFilhos++;
        if ((*p)->dir != NULL)
            numFilhos++;
        switch (numFilhos) {
            case 0: // nenhum filho
                free(*p); // apaga
                *p = NULL; // atualiza encadeamento
                return 0;
            case 1: // um filho
                aux = *p;
                *p = ((*p)->esq != NULL) ? (*p)->esq : (*p)->dir; // atualiza encadeamento
                free(aux);
                return 0;
            case 2: // dois filhos
                // acha maior filho na subarvore esquerda (aux)
                aux = (*p)->esq;
                paiAux = *p;
                while (aux->dir != NULL) {
                    paiAux = aux;
                    aux = aux->dir;
                }
                (*p)->info = aux->info; // copia info
                return (paiAux->esq == aux) ? abb_remocaoSub(&(paiAux->esq),aux->info) : abb_remocaoSub(&(paiAux->dir),aux->info); // apaga aux e atualiza encadeamento
        }
    }
    return (x < (*p)->info) ? abb_remocaoSub(&((*p)->esq), x) : abb_remocaoSub(&((*p)->dir), x);
}
int abb_eliminarElemento(void *av, int x){
	ABB *a = (ABB*) av;
    return abb_remocaoSub(&(a->raiz), x); // inicia recursao
}
