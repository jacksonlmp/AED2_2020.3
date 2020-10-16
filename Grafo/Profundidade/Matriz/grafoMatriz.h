#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct vertice {
	char ID;
	char *adjacentes;
	int tempo1;
	int tempo2;
	int cor;
	struct vertice* pai;
} vertice;

typedef struct grafo{
	FILE* arquivo;
	char* nome;
	int vertices;
	int arestas;
	vertice* elementos[100];
} grafo;

//Grafo
void criarGrafo(grafo *g, char *nome);
void lerArquivo(grafo* g);
void lerVertices(grafo* g);
void lerArestas(grafo* g);
void imprimirListaAdj(grafo *g);
void DSF(grafo* g, vertice* s);
void DSF_VISIT(vertice* s, vertice* inicial, vertice* vetor[], int tempo, int elementos);
vertice* procurarVertice(grafo *g, char nome);
vertice* carregarVertices(grafo* g);

#endif
