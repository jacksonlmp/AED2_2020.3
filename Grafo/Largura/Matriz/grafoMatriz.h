#ifndef GRAFOMATRIZ_H
#define GRAFOMATRIZ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct vertice {
	char ID;
	char *adjacentes;
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

typedef struct fila{
	vertice* vert;
	struct fila* prox;
} fila;

//Grafo
void criarGrafo(grafo *g, char *nome);
void lerArquivo(grafo* g);
void lerVertices(grafo* g);
void lerArestas(grafo* g);
void imprimirListaAdj(grafo *g);
void buscaLargura(grafo* g, vertice* s);
vertice* buscarVertice(grafo *g, char nome);
vertice* carregarVertices(grafo* g);

//Fila
fila* inserirFila(fila* aux, vertice* v);
fila* removerFila(fila* aux);
vertice* buscarInicio(fila* aux);

#endif
