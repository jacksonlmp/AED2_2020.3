#include <stdio.h>
#include <stdlib.h>
#include "listaAdjacencia.h"

int main(int argc, char *argv[]) {
    char origem;
    int v,a,i,j;
    char vertice, lixo, a1, a2;
    FILE *file;
    file = fopen("inf.txt", "r");

    if(file == NULL){
        printf("n foi possivel abrir o arquivo\n");
        exit(0);
    }

    fscanf(file, "%d %d", &v,&a); 
    grafo* gr = criarGrafo(v);  

    for(i = 0; i < v; i++){ 
        fscanf(file, "%c %c",&lixo,&vertice);
        addVertices(gr,vertice);
    }
   
    for(j=0; j < a; j++){ 
        fscanf(file, "%c %c%c", &lixo, &a1, &a2);
        addAresta(gr,a1,a2);
    }
    imprimirListaADJ(gr);
    
    printf("Digite um vertice de origem:\n");
    scanf("%c", &origem);

    buscaEmLargura(gr, origem);
    imprimirListaPosBusca(gr);
    
   
    fclose(file);
}
