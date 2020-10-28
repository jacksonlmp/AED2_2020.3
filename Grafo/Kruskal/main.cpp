#include <set>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include "kruskal.h"

int main(int argc, char **argv) {
    Grafo  *grafo = inicializaG();
    grafo = abrirArquivo(grafo, 0);

    imprimir(grafo->vertices);

    MST *mst = inicializaM();
    mst = MST_KRUSKAL(grafo);
    imprimirMST(mst);
}
