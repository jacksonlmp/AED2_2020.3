#include <stdio.h>
#include <stdlib.h>
#include "matricial.h"

int main(void){
    FILE *file;
    file = fopen("inf.txt", "r");

    if(file == NULL){
        printf("O arquivo esta vazio \n");
        exit(0);
    }

    int v,a,i,j;
    fscanf(file, "%d %d", &v,&a); 

    grafo* g = inicializarGrafo(v);
    char vertice,lixo,a1,a2;

    for(i = 0; i<v; i++){ 
        fscanf(file, "%c %c",&lixo,&vertice);
        addVertices(g,vertice,i);
    }

    for(j=0; j<a;j++){ 
       fscanf(file, "%c %c%c",&lixo,&a1,&a2);
       addArestaNaMatriz(g,a1,a2);
    }

    printf("\n%d vertices %d arestas\n", v,a);
    
    for(i = 0; i<v; i++){
        printf("v[%d]: %c ",i,g->vertices[i]);
    }

    imprimirGrafo(g);
    printf("\n");
    buscaEmLargura(g,'A');

    fclose(file);
}
