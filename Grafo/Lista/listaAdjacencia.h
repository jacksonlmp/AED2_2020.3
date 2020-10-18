#ifndef lista_H
#define lista_H
#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------LISTA
typedef enum CORES{BRANCO,CINZA,PRETO} COR;

typedef struct vertice{
    char letra;
    struct lista* adj;
    COR cor;
    struct vertice* pai;
    int dist;
    int tempoI;
    int tempoF;
}vertice;

typedef struct no{
    struct vertice* noVertice;
    struct no* prox;

}no;

typedef struct lista{
    struct no* inicial;

}lista;

lista* inicializarLista();
vertice* inicializar_vertice(char letra);

void inserirNaLista(lista* lista, vertice* vertice);
void imprimirLista(lista* lista);

//-----------------------------------------------------GRAFO
typedef struct grafo{
    int nmrVertices;
    lista* lista_v;
}grafo;

int buscarVertice(char v, lista* l);
void addVertices(grafo* g, char vert);

grafo* criarGrafo(int nmrV);
vertice* retornarVertice(char v, lista* l);

void addAresta(grafo* gr,char v1,char v2);
void imprimirListaADJ(grafo* gr);
//-----------------------------------------------------FILA

typedef struct noFila{
   struct vertice* noVertice;
   struct noFila* ant;
}noFila;

typedef struct fila{
   struct noFila* inicio;
   struct noFila* fim;
}fila;

int filaVazia(fila* fila);

fila* inicializarFila();

void inserirNaFila(fila* fila,vertice* v);
void removerDaFila(fila* fila);
void imprimirFila(fila* fila);
void buscaEmLargura(grafo* g, char origem);
void imprimirListaPosBusca(grafo* gr);

//------------------------------------------------------PILHA
typedef struct noPilha{
    struct vertice* noVertice;
    struct noPilha* proximo;
}noPilha;

typedef struct pilha{
    struct noPilha* topo;
}pilha;

pilha* inicializarPilha();

int pilhaVazia(pilha* pilha);
int visitarEmProfundidade(grafo* g, vertice* inicial, int tempo);

void push(pilha* pilha, vertice* v);
void pop(pilha* pilha);
void imprimirPilha(pilha* pilha);
void buscaEmProfundidade(grafo* g,int tempo);
void imprimirListaPosBuscaProf(grafo* g);
#endif
