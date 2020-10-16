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

  for(i=0; i < g->vertices; i++){
    aux->adjacentes[i] = '\0';
  }
  return aux;
}

void lerVertices(grafo* g){
  int i, j;
  for(i=0; i < g->vertices; i++){
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

vertice* procurarVertice(grafo *g, char nome){
      vertice* aux;
      for(aux = g->elementos; aux != NULL; aux = aux->prox){
        if(aux->ID == nome){
          return aux;
        }
      }
      return NULL;
}

void DSF_VISIT(vertice* s, vertice* inicial, vertice* vetor[], int tempo, int elementos){
	s->cor = 1;
	tempo++;
	s->tempo1 = tempo;
	vertice* aux;
	int i;
	for(i = 0; i<elementos; i++){
		for(int j = 0; j<elementos; j++){
			if(vetor[i]->ID == s->adjacentes[j]){
				if(s->cor == 0){
					vetor[i]->pai = s;
					DSF_VISIT(vetor[i], inicial, vetor, tempo, elementos);
				}
			}
		}
	}

	s->cor = 2;
	s->tempo2 = tempo++;
	if(s->ID != inicial->ID){
		printf("%s\n", &s->ID);
	}
}

void DSF(grafo* g, vertice* s){
	printf("A partir do vertice %s: \n", &s->ID);		
	vertice* aux;
	vertice* inicial = s;
	int i = 0;
	int j;
	int tempo = 0;
	vertice* vert[g->vertices];
	for(aux = g->elementos; aux!= NULL; aux = aux->prox){
		aux->cor = 0;
		aux->pai = NULL;
		vert[i] = (vertice*)malloc(sizeof(vertice));
		vert[i]->ID = aux->ID; 
		if(aux->ID == s->ID){
			j = i;
		}
		i++;
	}
	tempo = 0;
	for(aux = g->elementos; aux != NULL; aux= aux->prox){
		for(i=0; i<g->vertices; i++){
			if(vert[i]->ID == aux->ID){
				aux->cor = 0;
				DSF_VISIT(aux, inicial, vert, tempo, g->vertices);
			}
		}
	}
}


