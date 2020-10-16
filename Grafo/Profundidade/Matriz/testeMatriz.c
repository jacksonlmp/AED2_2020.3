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

    //BUSCA EM PROFUNDIDADE
	char nome;
	scanf("%c", &nome);
	vertice* v = procurarVertice(&g, nome);
	DSF(&g, v);
	exit(0);
}
