#include <stdio.h>
#include <stdlib.h>
#include "listaAdjacencia.h"

//--------------------------------------------------LISTA

lista* inicializarLista(){
    lista* nova = (lista*) malloc(sizeof(lista));
    nova->inicial=NULL;
    return nova;
}

vertice* inicializar_vertice(char letra){
    vertice* ver = (vertice*)malloc(sizeof(vertice));
    ver->letra = letra;
    ver->adj = inicializarLista();
    ver->cor = BRANCO;
    ver->dist = -1;
    ver->pai = NULL;
    ver->tempoI = 0;
    ver->tempoF = 0;
    return ver;
}
void inserirNaLista(lista* lista, vertice* vertice){
    no* novoNo = (no*) malloc(sizeof(no));
    novoNo->noVertice = vertice; //no que vai receber o inteiro e ser adicionado na lista
    if(lista->inicial==NULL){
        lista->inicial = novoNo; //adiciona o primeiro elemento
        novoNo->prox = NULL;
    }else{
        no* cursor = lista->inicial;
        while(cursor->prox!=NULL){
            cursor = cursor->prox;
        }
        novoNo->prox = NULL; // vai ser o ultimo da lista
        cursor->prox = novoNo;

    }
}
void imprimirLista(lista* lista){
    no* cursor;
    for(cursor=lista->inicial;cursor!=NULL;cursor= cursor->prox){
        printf("%c\n", cursor->noVertice->letra);
    }
}


//--------------------------------------------------FILA

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
   if(fila->inicio == NULL){
       fila->inicio = novo;
       fila->fim = novo;
   }
    else{
       fila->inicio->ant = novo;
       fila->inicio= novo;
   }
}

void removerDaFila(fila* fila){
    if(fila->fim != NULL){
       noFila* temp = fila->fim;
       fila->fim = temp->ant;
   }
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

//----------------------------------------------------------------GRAFO

grafo* criarGrafo(int nmrV){
    grafo* g = (grafo*)malloc(sizeof(grafo)); //aloquei memoria para o struct
    g->nmrVertices = nmrV;
    g->lista_v = inicializarLista();
    return g;
}

void addVertices(grafo* g, char vert){
    vertice* ver = inicializar_vertice(vert);
    inserirNaLista(g->lista_v,ver);
}

int buscarVertice(char v, lista* l){
    no* cursor;
    for(cursor = l->inicial; cursor != NULL; cursor = cursor->prox){
        if(cursor->noVertice->letra == v){
            return 1;
        }
    }
    return 0;
}

vertice* retornarVertice(char v, lista* l){
    no* cursor;
    for(cursor = l->inicial; cursor != NULL; cursor = cursor->prox){
        if(cursor->noVertice->letra == v){
            return cursor->noVertice;
        }
    }
    return NULL;
}

void addAresta(grafo* gr,char v1,char v2){ 
    no* cursor;
    for(cursor = gr->lista_v->inicial; cursor != NULL; cursor = cursor->prox){
        if(cursor->noVertice->letra == v1){
            if(buscarVertice(v2,gr->lista_v)){
                vertice* novo = retornarVertice(v2,gr->lista_v);
                inserirNaLista(cursor->noVertice->adj, novo);
                inserirNaLista(novo->adj, cursor->noVertice);
                break;
            }
        }
    }
}

void imprimirListaADJ(grafo* gr){
    no* cursor;
    no* cursor2;
    for(cursor = gr->lista_v->inicial; cursor != NULL;cursor = cursor->prox){
        printf("%c-> ", cursor->noVertice->letra);
        for(cursor2 = cursor->noVertice->adj->inicial; cursor2 != NULL;cursor2= cursor2->prox){
             printf("%c\t ", cursor2->noVertice->letra);
        }
        printf("\n");
    }

}

void buscaEmLargura(grafo* g, char origem){
    fila* fila = inicializarFila();
    vertice* raiz = retornarVertice(origem,g->lista_v);
    raiz->cor = CINZA;
    raiz->dist = 0;
    inserirNaFila(fila,raiz);
    
    no* cursor;
    for(cursor = raiz->adj->inicial; cursor != NULL; cursor = cursor->prox){
        cursor->noVertice->cor = CINZA;
        cursor->noVertice->dist = raiz->dist +1;
        cursor->noVertice->pai = raiz;
        inserirNaFila(fila,cursor->noVertice);
    }
    raiz->cor = PRETO;
    removerDaFila(fila);
    
    noFila* cursor2 = fila->fim;
    no* cursor3;

    while(!filaVazia(fila)){
        for(cursor3 = fila->fim->noVertice->adj->inicial; cursor3 != NULL; cursor3 = cursor3->prox){
            if(cursor3->noVertice->cor == BRANCO){
                 cursor3->noVertice->cor = CINZA;
                 cursor3->noVertice->dist = raiz->dist +1;
                 cursor3->noVertice->pai = cursor2->noVertice;
                 inserirNaFila(fila,cursor3->noVertice);
            }
        }
         cursor2->noVertice->cor = PRETO;
         removerDaFila(fila);
         cursor2 = cursor2->ant;
    }
}

void imprimirListaPosBusca(grafo* gr){
    no* cursor;
    for(cursor = gr->lista_v->inicial;cursor != NULL; cursor = cursor->prox){
        if(cursor->noVertice->pai == NULL){
            printf("%c - %d  %d-> ", cursor->noVertice->letra,cursor->noVertice->cor,cursor->noVertice->dist);
            printf("\n");
        }
        else{
            printf("%c %c %d  %d-> ", cursor->noVertice->letra,cursor->noVertice->pai->letra,cursor->noVertice->cor,cursor->noVertice->dist);
            printf("\n");
        }
    }
}

void buscaEmProfundidade(grafo* g,int tempo){
    no* cursor = g->lista_v->inicial;
    while(cursor != NULL){
        if(cursor->noVertice->cor == BRANCO){
            tempo = visitarEmProfundidade(g,cursor->noVertice,tempo);
        }
        cursor = cursor->prox;
    }

    cursor =  g->lista_v->inicial; 
    while(cursor != NULL){
        printf("%c - %d/%d\n", cursor->noVertice->letra, cursor->noVertice->tempoI, cursor->noVertice->tempoF);
        cursor = cursor->prox;
    }
}

int visitarEmProfundidade(grafo* g, vertice* inicial, int tempo){
    inicial->cor = CINZA;
    tempo = tempo +1;
    inicial->tempoI = tempo;

    no* cursor = inicial->adj->inicial;

    while(cursor != NULL){
        if(cursor->noVertice->cor==BRANCO){
            cursor->noVertice->pai = inicial;
            tempo = visitarEmProfundidade(g,cursor->noVertice, tempo);
        }
        cursor = cursor->prox;
    }

    inicial->cor = PRETO;
    tempo = tempo + 1;
    inicial->tempoF = tempo;

    return tempo;
}

void imprimirListaPosBuscaProf(grafo* g){
    no* cursor = g->lista_v->inicial;
    while(cursor!=NULL){
        printf("%c - %d  %d %d ", cursor->noVertice->letra,cursor->noVertice->cor,cursor->noVertice->tempoI,cursor->noVertice->tempoF);
        printf("\n");
        cursor = cursor->prox;
    }
}


