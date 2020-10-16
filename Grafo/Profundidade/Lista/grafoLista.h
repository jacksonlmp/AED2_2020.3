#ifndef GRAFOLISTA_H
#define GRAFOLISTA_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vertice {
	char ID;
	int cor;
	int tempo1;
	int tempo2;
	char *adjacentes;
	struct vertice* prox;
	struct vertice* pai;
} vertice;

typedef struct grafo{
	FILE* arquivo;
	char* nome;
	vertice* elementos;
	int vertices;
	int arestas;
} grafo;

//GRAFO
void criarGrafo(grafo *g, char *nome);
void lerArquivo(grafo* g);
void lerVertices(grafo* g);
void lerArestas(grafo* g);
void imprimirListaAdj(grafo *g);
void DSF(grafo* g, vertice* s);
void DSF_Visit(vertice* s, vertice* inicial, vertice* vetor[], int tempo, int elementos);
vertice* procurarVertice(grafo *g, char nome);
vertice* carregarVertices(grafo* g);

#endif
