#ifndef matriz_H
#define matriz_H
#include <stdio.h>
#include <stdlib.h>

typedef enum CORES{BRANCO,CINZA,PRETO} COR;

typedef struct vertice{
    char letra;
    COR cor;
    struct vertice* pai;
    int dist;
    int tempoI;
    int tempoF;
}vertice;

typedef struct grafo{
    int nmrVertices;
    int **matriz;
    char * vertices;
}grafo;

grafo* inicializarGrafo(int nmrV);
vertice* inicializarVertice(char letra);
vertice* retornarVertice(grafo*,char v);

void addVertices(grafo* g, char vert, int indice);
void addAresta(grafo* gr,char v1,char v2);
void imprimirGrafo(grafo* g);
int retornarIndiceVertice(grafo* g, char v);

//-------------------------------------------------FILA

typedef struct noFila{
   struct vertice* noVertice;
   struct noFila* ant;
}noFila;

typedef struct fila{
   struct noFila* inicio;
   struct noFila* fim;
}fila;

fila* inicializarFila();
vertice* removerDaFila(fila* fila);

void inserirNaFila(fila* fila,vertice* v);
void imprimirFila(fila* fila);
void buscaEmLargura(grafo* g, char origem);
void imprimirListaPosBusca(grafo* gr);
void buscaEmProfundidade(grafo* g, int tempo);

int filaVazia(fila* fila);
int verificarADJ(grafo* g,char vert1,char vert2);
int visitarEmProfundidade(grafo* g,  int tempo, vertice* inicial, vertice* vetor[]);
#endif
