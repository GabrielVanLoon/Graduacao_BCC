#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "pilha.h"

/** @Prototipos de funções auxiliares **/
    int     _avl_qtdFilhos(NoAVL *p);
    int     _avl_altura(NoAVL *p);
    int     _avl_fatorCarga(NoAVL *p);
    NoAVL*  _avl_criarNo(elem_AVL info, NoAVL *esq, NoAVL *dir, int fb, int altura);

/** @Rotações e Atualizações do Fator **/
    void _avl_rotacionar(NoAVL **p);
    void _avl_E(NoAVL **p);
    void _avl_D(NoAVL **p);
    void _avl_ED(NoAVL **p);
    void _avl_DE(NoAVL **p);

/** @void avl_criarArvore(void *av);
 */
    void avl_criarArvore(void *av){
        AVL* a = (AVL*) av;
        a->raiz = NULL;
        return;
    }

/** @void avl_finalizarArvore(void *av);
 */
    void _avl_destroiSub(NoAVL *p) {
        if (p == NULL)
            return;
        _avl_destroiSub(p->esq);
        _avl_destroiSub(p->dir);
        free(p);
        return;
    }
    void avl_finalizarArvore(void *av) {
        AVL* a = (AVL*) av;
        _avl_destroiSub(a->raiz); // inicia recursao
        a->raiz = NULL;
        return;
    }

/** @int avl_estaVazia(void *av);
 */
    int avl_estaVazia(void *av) {
        AVL* a = (AVL*) av;
        return a->raiz == NULL;
    }

/** @int avl_estaVazia(void *av);
 */
    int _avl_alturaSub(NoAVL *p) {
        int altura_esq, altura_dir;
        if (p == NULL)
            return 0; // arvore nula
        altura_esq = _avl_alturaSub(p->esq);
        altura_dir = _avl_alturaSub(p->dir); 
        return (altura_esq > altura_dir)? altura_esq + 1 : altura_dir + 1;
    }
    int avl_altura(void *av) {
        AVL* a = (AVL*) av;
        return _avl_alturaSub(a->raiz);
    }

/** @int avl_buscarElemento(void* av, int x);
 */
    int _avl_buscaSub(NoAVL *p, elem_AVL x) {
        if (p == NULL) return 0; 
        if (p->info == x) return 1; 
        return (x < p->info) ? _avl_buscaSub(p->esq, x) : _avl_buscaSub(p->dir, x);
    }
    int avl_buscarElemento(void* av, int x) {
        AVL* a = (AVL*) av;
        return _avl_buscaSub(a->raiz, x); // inicia recursao
    }

/** @int avl_inserirElemento(void* av, int x);
 */ 
    int _avl_insercaoSub(NoAVL **p, elem_AVL x) {
        
        int retorno = 0;

        /* 1º - Inserindo a nova folha e retornando o parametro avisando que a 
         *      a subarvore cresceu.
         */ 
        if (*p == NULL) {
            *p = _avl_criarNo(x, NULL, NULL, 0, 1);
            return (*p == NULL) ? 1 : 0;
        }

        /* 2º - Caso o elemento já exista na árvore, retorna erro.
         */
        if ((*p)->info == x) return 1;
        
        /* 3º - Inserindo na subarvore da esquerda ou da direita
         */
        if( x < (*p)->info)
            retorno = _avl_insercaoSub(&((*p)->esq), x);
        else 
            retorno = _avl_insercaoSub(&((*p)->dir), x);

        /* 4º - A inserção não foi feita, então retorna erro.
         */
        if(retorno)
            return retorno;

        /* 5º - Realizando a rotação. */
        _avl_rotacionar(p);

        return retorno;
    }
    int avl_inserirElemento(void* av, int x) {
        AVL* a = (AVL*) av;
        return _avl_insercaoSub(&(a->raiz), x); // inicia recursao
    }

/** @int avl_eliminarElemento(void* av, int x);
 */ 
    int _avl_removerMaxEsq(NoAVL **p, NoAVL **raiz){
        // Função especifica para remoção no caso de 2 filhos.
        int retorno = 0;
        NoAVL *aux;

        /* Achou o maior nó da sub da esquerda, joga sua informação no nó da 
         * raíz que está sendo excluida e então o remove.
         */
        if((*p)->dir == NULL){
            (*raiz)->info = (*p)->info;
            
            aux = (*p); 
            (*p) = aux->esq;
            free(aux);
            return 0;
        }

        /* Avançando a recursão para o filho à direita. */
       retorno = _avl_removerMaxEsq(&((*p)->dir), raiz);

        /* Ajustando a rotação do nó */
        _avl_rotacionar(p);

        return retorno;
    }
    int _avl_remocaoSub(NoAVL **p, elem_AVL x){

        int   retorno = 0, qtdFilhos;
        NoAVL *aux;

        /* Não encontrou o elemento, retorna 1 */ 
        if (*p == NULL) return 1;

        /* 1º - Encontrou o elemento, agora o remove. */
        if ((*p)->info == x) {
            qtdFilhos = _avl_qtdFilhos(*p);

            /* 0 Filhos: Remove e ajusta o ponteiro do pai. 
             * 1 Filhos: Remove e o ponteiro do pai aponta para o filho.
             * 2 Filhos: Substitui o valor do nó com o valor do maior filho
             *           da subarvore da direita e exclui o nó do maior filho.
             */
            if(qtdFilhos == 0){
                aux = (*p);
                *p = NULL;
                free(aux);
                return 0;

            } else if(qtdFilhos == 1){
                aux = (*p);
                (*p) = (aux->esq != NULL) ? aux->esq : aux->dir;
                free(aux);
                return 0;

            } else {
                //Função especifica para remoção no caso de 2 filhos.
                _avl_removerMaxEsq(&((*p)->esq), &(*p));
                _avl_rotacionar(p);
                return 0;
            }

        }

        /* 2º - Descendo a recursão para a esquerda ou direita
         */
        if( x < (*p)->info)
            retorno = _avl_remocaoSub(&((*p)->esq), x);
        else 
            retorno = _avl_remocaoSub(&((*p)->dir), x);

        /* 3º - A inserção não foi feita, então retorna erro. */
        if(retorno)
            return retorno;

        /* 4º - Realiza a rotação.*/
        _avl_rotacionar(p);

        return retorno;
    }
    int avl_eliminarElemento(void* av, int x){
        AVL* a = (AVL*) av;
        return _avl_remocaoSub(&(a->raiz), x);
    }

/**@void avl_printInOrdem(void* av);
 */
    void _avl_printInOrdemSub(NoAVL *p) {
        if (p == NULL) return;
        _avl_printInOrdemSub(p->esq);
        printf("%d[%d] ", p->info, p->altura);
        _avl_printInOrdemSub(p->dir);
    }
    void avl_printInOrdem(void* av){
        AVL* a = (AVL*) av;
        _avl_printInOrdemSub(a->raiz);
        printf("\n");
    }

/** Funções auxiliares **/
    int _avl_qtdFilhos(NoAVL* p){
        if(p->esq != NULL && p->dir != NULL) return 2;
        if(p->esq != NULL || p->dir != NULL) return 1;
                                             return 0;  
    }

    NoAVL*  _avl_criarNo(elem_AVL info, NoAVL *esq, NoAVL *dir, int fb, int altura) {
        NoAVL *no = malloc(sizeof(NoAVL));
        if (no != NULL) {
            no->info    = info;
            no->esq     = esq;
            no->dir     = dir;
            no->fb      = fb;
            no->altura  = altura;
        }
        return no;
    }

    int _avl_altura(NoAVL *p){
        if(p == NULL) return 0;

        if(p->esq != NULL && p->dir != NULL)
            return 1 + ((p->esq->altura > p->dir->altura)? p->esq->altura : p->dir->altura); 
        
        if(p->esq != NULL)
            return (1 + p->esq->altura);

        if(p->dir != NULL)
            return (1 + p->dir->altura);
                      
        return 1;
    }

    int _avl_fatorCarga(NoAVL *p){
        if(p == NULL) return 0;

        if(p->esq != NULL && p->dir != NULL)
            return (_avl_altura(p->dir) - _avl_altura(p->esq));
        
        if(p->esq != NULL)
            return (-1*_avl_altura(p->esq));

        if(p->dir != NULL)
            return (+1*_avl_altura(p->dir));
                      
        return 0;
    }

/** @Rotações e Atualizações do Fator **/
    void _avl_rotacionar(NoAVL **p){
        (*p)->altura = _avl_altura(*p);
        (*p)->fb     = _avl_fatorCarga(*p);

        /* Caso (fb == 2)  >> A árvore se desbalanceou para a direita
         * Caso (fb == -2) >> A árvore se desbalanceou para a esquerda
         */
        if( (*p)->fb == 2 && (*p)->dir->fb >= 0)
            _avl_E(p);
        else if((*p)->fb == 2 && (*p)->dir->fb == -1)
            _avl_DE(p);
        
        if( (*p)->fb == -2 && (*p)->esq->fb <= 0)
            _avl_D(p);
        else if((*p)->fb == -2 && (*p)->esq->fb == 1)
            _avl_ED(p);
    }

    void _avl_E(NoAVL **p){
        NoAVL *novoRaiz, *realocar;
        
        /* O filho da direita será a nova raíz e, se ele tiver algum filho
         * à esquerda, realoca este como filho à direita do nó em rotação.
         */
        novoRaiz = (*p)->dir;
        realocar = novoRaiz->esq;
        
        novoRaiz->esq = (*p);
        (*p)->dir = realocar;
        
        // Ajusta o pai do nó em rotação para apontar para a nova raíz.
        (*p) = novoRaiz;

        // Atualizando a altura da raiz e do nó que foi rodado.
        novoRaiz->esq->altura = _avl_altura(novoRaiz->esq);
        novoRaiz->altura = _avl_altura(novoRaiz);
        

        // Atualizando o fator de carga da nova raiz e da antiga raiz
        novoRaiz->esq->fb = _avl_fatorCarga(novoRaiz->esq);
        novoRaiz->fb = _avl_fatorCarga(novoRaiz);

        return;
    }

    void _avl_D(NoAVL **p){
        NoAVL *novoRaiz, *realocar;

        /* O filho da esquerda será a nova raíz e, se ele tiver algum filho
         * à direita, realoca este como filho à esquerda do nó em rotação.
         */
        novoRaiz = (*p)->esq;
        realocar = novoRaiz->dir;

        novoRaiz->dir = (*p);
        (*p)->esq = realocar;

        // Ajusta o pai do nó em rotação para apontar para a nova raíz.
        (*p) = novoRaiz;

        // Atualizando a altura da raiz e do nó que foi rodado.
        novoRaiz->dir->altura   = _avl_altura(novoRaiz->dir);
        novoRaiz->altura        = _avl_altura(novoRaiz);
        

        // Atualizando o fator de carga da nova raiz e da antiga raiz
        novoRaiz->dir->fb   = _avl_fatorCarga(novoRaiz->dir);
        novoRaiz->fb        = _avl_fatorCarga(novoRaiz);
        
        return;
    }

    void _avl_ED(NoAVL **p){
        /* Faz uma rotação à esquerda no filho da esquerda e em seguida uma
         * rotação à direita no nó atual.
         */
        _avl_E(&((*p)->esq));
        _avl_D(p);
        return;
    }

    void _avl_DE(NoAVL **p){
        /* Faz uma rotação à direita no filho da direita e em seguida uma
         * rotação à esquerda no nó atual.
         */
        _avl_D(&((*p)->dir));
        _avl_E(p);
        return;
    }