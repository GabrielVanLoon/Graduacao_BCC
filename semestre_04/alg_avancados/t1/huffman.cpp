/**
 * T1 Algoritmos Avançaçdos - Código Huffman
 * 
 * OBJETIVO: 
 * Encontrar a árvore do código de Huffman dado um texto
 * escrito em ASCII qualquer.
 * 
 * ENTRADAS: 
 * Um texto em ASCII qualquer tal que o fim de texto termine com um \n.
 * 
 * SAIDA:
 * Arvore de Huffman exibida da camada superior até a camada interior (BFS) mostrando
 * a contagem das frequencias (e o char associado, no caso de nós folhas).
 * 
 * Além disso, também exibe
 */
#include <iostream>
#include <algorithm>
#include <vector> 
#include <queue> 
#include <stdlib.h>

// Struct feita para representar os Nós da Árvore de Huffman
typedef struct _no {
    int  freq;
    char ascii;
    bool ehFolha;
    bool ehRaiz;
    struct _no *l, *r;
    int  altura;
} No;

struct CompararNos { 
    bool operator()(No* const& n1, No* const& n2){ 
        return n1->freq > n2->freq; // Ordena decrescente
    } 
}; 

// Vetor de Nós tal que No.ascii = freq[ascii]
// Utilizado na etapa de processamento do texto.
No freq[300];

// Vetor extra para criação de novos nós sem se preocupar com
// mallocs, reallocs e ponteiros perdidos sendo @e o iterador.
No extra[300];
int e;

// Fila de prioridade para retornar o Nó com menor frequencia
std::priority_queue<No*, std::vector<No*>, CompararNos> pq;

/**
 * Exibe na tela a árvore gerada pelo Código Huffman utilizando uma BFS para imprimir
 * camada por camada.
 */
void printBFS(No* root);

/**
 * Exibe uma tabela associando cada char com sua frequencia e seu código binário
 * de compressão.
 */
char strCodigo[300];
void printCodigos(No* n);

int main(void){
    
    printf("Código Huffman\n");

    // 1ª Etapa - Ler os caracteres e somar sua frequencia.
    char c;
    scanf("%c", &c);
    while(c != '\n'){
        freq[c].freq += 1;
        freq[c].ascii = c;
        scanf("%c", &c);    
    }

    // 2ª Etapa - Analisa as Frequencias geradas. Os caracteres que aparecerem ao menos 1 vez
    //            serão nós valídos e serão adicionados à Heap.
    printf("\nFrequências por caracter:\n");
    for(int i = 0; i < 300; i++){
        if(freq[i].freq > 0){
            printf("'%c' %d\n", freq[i].ascii, freq[i].freq);
            freq[i].ehRaiz  = true;
            freq[i].ehFolha = true;
            freq[i].l = freq[i].r = NULL;
            pq.push(&freq[i]);
        }
    }

    // 3º Etapa - Remove os nós da Heap com menos frequencia e vai montando uma nova árvore
    while(pq.size() > 1){
        //No* n = pq.top(); pq.pop();
        //printf("%c %d\n", n->ascii, n->freq);
        No* nl = pq.top(); pq.pop();
        No* nr = pq.top(); pq.pop();
        
        extra[e] = {nl->freq+nr->freq, ' ', false, true, nl, nr, 0};
        pq.push(&extra[e]);
        e++;   
    }

    // 4ª Etapa - Exibe o print da Árvore utilizando uma BFS e por fim a tabela dos códigos gerados.
    No* root = pq.top();
    printBFS(root);
    printCodigos(root);
    


    return 0;
}

void printBFS(No* root){

    printf("\nÁrvore Gerada:\n");

    std::queue<No*> q;
    int alturaAtual = root->altura;
    q.push(root);

    while(!q.empty()){
        No* n = q.front(); q.pop();
        
        // Enfileira os filhos e atualiza altura deles.
        if(n->l != NULL){ 
            q.push(n->l);
            n->l->altura = n->altura + 1;
        }
        if(n->r != NULL){
            q.push(n->r);
            n->r->altura = n->altura + 1;
        } 

        // Exibe na tela o Nó atual
        if(n->altura == alturaAtual){
            printf("{%d,%d,'%c'}   ", n->freq, n->ehFolha, n->ascii);
        }else {
            alturaAtual = n->altura;
            printf("\n{%d,%d,'%c'}   ", n->freq, n->ehFolha, n->ascii);
        }
    }
}

void printCodigos(No* n){
   
    if(n->altura == 0)
        printf("\n\nCaracter\tFrequencia\tCódigo\n");
   
    // Caso de parada - n eh folha
    if(n->ehFolha){
        strCodigo[n->altura] = '\0';
        printf("'%c'\t\t%d\t\t%s\n", n->ascii, n->freq, strCodigo);
    
    } else {
        strCodigo[n->altura] = '0';
        printCodigos(n->l);

        strCodigo[n->altura] = '1';
        printCodigos(n->r);
    }
}