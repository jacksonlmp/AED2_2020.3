#include <stdio.h>
#include <stdlib.h>
#include "matricial.h"

grafo* inicializarGrafo(int nmrV){
    int i,j;
    grafo* gr = (grafo*) malloc(sizeof(grafo));
    gr->nmrVertices = nmrV;
    gr->matriz = (int**)malloc(sizeof(int*)*nmrV);
    gr->vertices = (char*)malloc(sizeof(char)*nmrV);
  
    for(i = 0;i < nmrV; i++){
        gr->matriz[i] = (int*) malloc(sizeof(int)*nmrV);
    }
    
    for(i = 0; i < nmrV; i++){
        for(j = 0; j < nmrV; j++){
            if(i == j){
               gr->matriz[i][j]=1;
            }
            else{
                gr->matriz[i][j]=0;
            }
        }
    }
    return gr;
}

vertice* inicializarVertice(char letra){
    vertice* ver = (vertice*)malloc(sizeof(vertice));
    ver->letra = letra;
    ver->cor = BRANCO;
    ver->dist = -1;
    ver->pai = NULL;
    ver->tempoI=0;
    ver->tempoF = 0;
    return ver;
}

void addVertices(grafo* g, char vert, int indice){
    g->vertices[indice] = vert;
}

int retornarIndiceVertice(grafo* g, char v){
    int i;
    for(i = 0; i < g->nmrVertices; i++){
        if(g->vertices[i] == v){
            return i;
        }
    }
    return 0;
}

int verificarADJ(grafo* g,char vert1,char vert2){
    int i = retornarIndiceVertice(g,vert1);
    int j = retornarIndiceVertice(g,vert2);

    if(g->matriz[i][j] == 1){
        return 1;
    }
    return 0;  
}

void addArestaNaMatriz(grafo* g,char a1,char a2){
    int i, p1,p2;
   
    for(i = 0; i < g->nmrVertices; i++){
        if(a1 == g->vertices[i]){
            p1 = i;
        }
        if(a2 == g->vertices[i]){
            p2 = i;
        }
    }
    g->matriz[p1][p2] = 1;
    g->matriz[p2][p1] = 1;
}

void imprimirGrafo(grafo* g){
    int i, j;
    for(i = 0; i < g->nmrVertices; i++){
        printf("\n");
        for(j = 0; j < g->nmrVertices; j++){
            printf(" %d ", g->matriz[i][j]);
        }
    } 
}

//-------------------------------------------------FILA
fila* inicializarFila(){
   fila* fila = malloc(sizeof(fila));
   fila->inicio = NULL;
   fila->fim = NULL;
   return fila;
}

void inserirNaFila(fila* fila,vertice* v){
   noFila* novo = (noFila*) malloc(sizeof(noFila));
   novo->noVertice = v;
   novo->ant = NULL;

   if(filaVazia(fila)){
       fila->inicio = novo;
       fila->fim = novo;
   }
    else{
       fila->inicio->ant = novo;
       fila->inicio= novo;
   }
}

vertice* removerDaFila(fila* fila){
    noFila* temp = NULL;
    if(fila->fim != NULL){
       temp = fila->fim;
       fila->fim = temp->ant;
   }
   return temp->noVertice;
}

int filaVazia(fila* fila){
    if(fila->fim == NULL){
        return 1;
    }
    return 0;
}

void imprimirFila(fila* fila){
    noFila* cursor = fila->fim;
    while(cursor->ant != NULL){
        printf("%c\n", cursor->noVertice->letra);
        cursor = cursor->ant;
    }
     printf("%c\n", cursor->noVertice->letra);
}


void buscaEmLargura(grafo* g, char origem){
    int k;
    fila* fila = inicializarFila();
    vertice* vetor[g->nmrVertices];    

    for(k = 0; k < g->nmrVertices; k++){
        vetor[k] = inicializarVertice(g->vertices[k]);
    }

    vertice* raiz;
     for(k = 0; k < g->nmrVertices; k++){
        if(vetor[k]->letra==origem){
            raiz = vetor[k];
        }
    }

    raiz->cor = CINZA;
    raiz->dist = 0;
    inserirNaFila(fila,raiz);
    vertice* vertice;

    while(!filaVazia(fila)){
        vertice = removerDaFila(fila);
        for( k = 0; k < g->nmrVertices; k++){
            if(verificarADJ(g,vertice->letra,vetor[k]->letra)){
                if(vetor[k]->cor==BRANCO){
                    vetor[k]->cor = CINZA;
                    vetor[k]->dist = vertice->dist + 1;
                    vetor[k]->pai =  vertice;
                    inserirNaFila(fila,vetor[k]);
                }
            }
        }
        vertice->cor = PRETO;          
    }

    for( k = 0; k < g->nmrVertices; k++){
        printf("cor: %d , dist: %d",vetor[k]->cor, vetor[k]->dist);
        printf("\n");
    }

}

void buscaEmProfundidade(grafo* g, int tempo){
    int k;
    vertice* vetor[g->nmrVertices];    

    for(k = 0; k < g->nmrVertices; k++){
        vetor[k] = inicializarVertice(g->vertices[k]);
    }

    for(k = 0; k < g->nmrVertices; k++){
        if(vetor[k]->cor == BRANCO){
            int tempo = visitarEmProfundidade(g,0,vetor[k],vetor);
        }
    }

    for(k = 0; k < g->nmrVertices; k++){
        printf("\n%c - %d/%d\n",vetor[k]->letra,vetor[k]->tempoI,vetor[k]->tempoF);
    }
}

int visitarEmProfundidade(grafo* g,int tempo,vertice* inicial,vertice* vetor[]){
    int k;
    inicial->cor =CINZA;
    tempo = tempo +1;
    inicial->tempoI = tempo;
    
    for(k = 0; k < g->nmrVertices; k++){
        if(verificarADJ(g,inicial->letra,vetor[k]->letra)){
            if(vetor[k]->cor == BRANCO){
                vetor[k]->pai =  inicial;
                tempo = visitarEmProfundidade(g,tempo,vetor[k],vetor);
            }
        }
    }

    inicial->cor = PRETO;
    tempo = tempo +1;
    inicial->tempoF = tempo;
    return tempo;
}
