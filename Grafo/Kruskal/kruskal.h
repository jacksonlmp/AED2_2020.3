#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {BRANCO, CINZA, PRETO} COR;

struct lista{
    struct vertice *vertice;
    struct lista *prox;
}; typedef struct lista Lista;

struct vertice{
    char letra[2];
    struct vertice *prox;
    Lista *proxElemento;
    struct vertice *pai;
}; typedef struct vertice Vertice;

struct aresta{
    Vertice *u;
    Vertice *v;
    int peso;
    struct aresta *prox;
}; typedef struct aresta Aresta;

struct grafo{
    Vertice *vertices;
    Aresta *arestas;
}; typedef struct grafo Grafo;

struct conjunto{
    struct conjunto *prox;
    Lista *lista;
    int tamanho;
}; typedef struct conjunto Conjunto;

struct mst{
    struct mst *prox;
    Aresta *aresta;
}; typedef struct mst MST;

Vertice *inicializaV(void);
Lista *inicializaL(void);
Grafo *inicializaG(void);
Aresta *inicializaA(void);
MST *inicializaM(void);

Vertice *insere_inicioVertice(Vertice *v, char letra);
Vertice *retornaVertice(Vertice *v, char letra);

Lista *insere_inicioLista(Lista *l, Vertice *v);
Aresta *insere_crescenteAresta(Aresta *aresta, Vertice *v, Vertice *u, int peso);

MST *insere_MST(MST *arv, Aresta *a);
MST *MST_KRUSKAL(Grafo *G);

Grafo *abrirArquivo(Grafo *grafo, int direcional);

Conjunto *MAKE_SET(Vertice *v, Conjunto *W);
Conjunto *FIND_SET(Vertice *v, Conjunto *W);
Conjunto *UNION(Conjunto *v, Conjunto *u, Conjunto *W);
Conjunto *REMOVER_SET(Conjunto *v, Conjunto *W);

void imprimirLista(Lista *l);
void imprimir(Vertice *v);
void imprimirArestas(Aresta *l);
void imprimirConjunto(Conjunto *l);
void imprimirMST(MST *l);

#endif
