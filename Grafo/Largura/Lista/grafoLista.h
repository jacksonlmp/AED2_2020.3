#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct vertice {
	char ID;
	char *adjacentes;
	struct vertice* prox;
} vertice;

typedef struct grafo{
	char* nome;
	int vertices;
	int arestas;
    vertice* elementos;
    FILE* arquivo;
} grafo;

typedef struct fila{
	vertice* vert;
	struct fila* prox;
} fila;

//GRAFO
void criarGrafo(grafo *g, char *nome);
void lerArquivo(grafo* g);
void lerVertices(grafo* g);
void lerArestas(grafo* g);
void imprimirListaAdj(grafo *g);
void buscaLargura(grafo* g, vertice* s);
vertice* carregarVertices(grafo* g);
vertice* procurarVertice(grafo *g, char nome);

//FILA
fila* inserirFila(fila* f, vertice* v);
fila* retirarFila(fila* f);
vertice* buscarInicio(fila* f);

#endif
