#include <stdio.h>
#include <stdlib.h>
#include "grafoMatriz.h"

int main(int argc, char * argv[]) {
	grafo g;

	char arquivo[15] = "grafo";
	criarGrafo(&g, arquivo);
	lerArquivo(&g);
	lerVertices(&g);
	lerArestas(&g);
	imprimirListaAdj(&g);

    //Busca em Largura
	char nome;
	scanf("%c", &nome);
	vertice* v = buscarVertice(&g, nome);
	buscaLargura(&g, v);
	exit(0);
}
