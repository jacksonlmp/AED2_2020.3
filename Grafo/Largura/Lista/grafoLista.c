#include "grafoLista.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void criarGrafo(grafo *g, char *nome){
  g->nome = strdup(nome);
  g->arquivo = fopen(nome, "r");

  if(g->arquivo == NULL){
	printf("Arquivo não encontrado");    
	exit(1);
  }
  g->elementos = NULL;
}

void lerArquivo(grafo* g){
  char *aux;
  char buffer[16];

  fgets(buffer, 15, g->arquivo);
  aux = strtok(buffer," ");

  if(aux != NULL){
    g->vertices = atoi(aux);
    aux = strtok(NULL,"\n");
    g->arestas = atoi(aux);
  }
}

vertice* carregarVertices(grafo* g){
    int i;

    vertice* aux = (vertice*)malloc(sizeof(vertice));
    aux->ID = fgetc(g->arquivo);
    fgetc(g->arquivo);
    aux->adjacentes = (char*)malloc(g->vertices * sizeof(char));

    for(i = 0; i < g->vertices; i++){
        aux->adjacentes[i] = '\0';
    }
    return aux;
}

void lerVertices(grafo* g){
    int i, j;
    for(i = 0; i < g->vertices; i++){
        vertice* aux = carregarVertices(g);
        aux->prox = g->elementos;
        g->elementos = aux;
    }
}

void lerArestas(grafo* g){
    int i, j;
    char v1, v2;
    vertice* aux;

    for(i=0; i < g->arestas; i++){
        v1 = fgetc(g->arquivo);
        v2 = fgetc(g->arquivo);
        fgetc(g->arquivo);

        for(aux = g->elementos; aux != NULL && aux->ID != v1; aux = aux->prox);
            for(j=0; aux != NULL && aux->adjacentes[j] != '\0'; j++);
                if(aux != NULL){
                  aux->adjacentes[j] = v2;
                }

            if(v1 != v2){
              for(aux = g->elementos; aux != NULL && aux->ID != v2; aux = aux->prox);
                  for(j=0; aux != NULL && aux->adjacentes[j] != '\0'; j++);
                      if(aux != NULL){
                        aux->adjacentes[j] = v1;
                      }
              }
    }
}

void imprimirListaAdj(grafo *g){
    int i, j;
    vertice* aux = g->elementos;

    for(i=0; aux != NULL && i < g->vertices; i++){
        printf("%c: ", aux->ID);
        j = 0;

        while(aux->adjacentes[j] != '\0'){
          printf("%c ", aux->adjacentes[j]);
          j++;
        }
        printf("\n");
        aux = aux->prox;
    }
}

fila* inserirFila(fila* aux, vertice* v){
    fila* nova = aux;
    if(nova == NULL){
	    nova = (fila*)malloc(sizeof(fila));
	    nova->vert = v;
	    nova->prox = NULL;
	    return nova;
    }
    if(nova->prox == NULL){
	    nova->prox = (fila*)malloc(sizeof(fila));
	    nova->prox->vert = v;
	    nova->prox->prox = NULL;
	    return nova;		
    }
    nova->prox = inserirFila(nova->prox, v);
    return nova;
}

fila* retirarFila(fila* aux){
    fila* nova = aux;
    if(nova == NULL){
	    return NULL;
    }
    if(nova->prox == NULL){
	    return NULL;
    }
    return nova->prox;
}

vertice* buscarInicio(fila* aux){
	fila* g = aux;
	if(g == NULL){
		return NULL;
	}
	if(g->vert != NULL){
		return g->vert;
	}
}

vertice* procurarVertice(grafo *g, char nome){
    vertice* aux;
    for(aux = g->elementos; aux != NULL; aux = aux->prox){
        if(aux->ID == nome){
          return aux;
        }
    }
    return NULL;
}

void buscaLargura(grafo* g, vertice* s){
    fila* pi = NULL;	
    vertice* aux;

    int i = 0;
    int j;
    int cor[g->vertices];

    vertice* pai[g->vertices];
    vertice* vert[g->vertices];

    for(aux = g->elementos; aux!= NULL; aux = aux->prox){
	    cor[i] = 0;
	    pai[i] = NULL;
	    vert[i] = (vertice*)malloc(sizeof(vertice));
	    vert[i]->ID = aux->ID; 
	    if(aux == s){
		    j = i;
	    }
	    i++;
    }

    cor[j] = 1;
    pi = inserirFila(pi, s);
    int posicao = 0;

    while(pi != NULL){
	    aux = buscarInicio(pi);
	    for(i=0; i<g->vertices; i++){		
		    if(vert[i]->ID == aux->ID){
			    posicao = i;
		    }
	    }
	    for(i=0; i<g->vertices; i++){
		    for(j=0; j<g->vertices; j++){
			    if((aux->adjacentes[j] == vert[i]->ID)&&(cor[i]==0)){		
				    cor[i] = 1;
				    pai[i] = aux;
				    vertice* vert = procurarVertice(g, aux->adjacentes[j]);
				    pi = inserirFila(pi, vert);
			    }
		    }
	    }
	    pi = retirarFila(pi);
	    cor[posicao] = 2;		
    }
    printf("A partir do vertice %s:\n", &s->ID);
    for(i=0; i<g->vertices; i++){
	    if((cor[i] == 2)&&(vert[i]->ID!=s->ID)){
		    printf("%s\n", &vert[i]->ID);
	    }
    }
}
