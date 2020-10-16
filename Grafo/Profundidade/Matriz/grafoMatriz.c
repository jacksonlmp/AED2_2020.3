#include "grafoMatriz.h"
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
	for(int i=0; i<100; i++){
		g->elementos[i] = NULL;
	}
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
		g->elementos[i] = aux;
	}
}

void lerArestas(grafo* g){
	int i, j;
	vertice* aux;
	char v1, v2;
	for(i=0; i < g->arestas; i++){
		v1 = fgetc(g->arquivo);
		v2 = fgetc(g->arquivo);
		fgetc(g->arquivo);
		for(i=0; i<100; i++){
			aux = g->elementos[i];
			if((aux == NULL)||(aux->ID == v1)){
				break;
			}
		}    
		for(j=0; aux != NULL && aux->adjacentes[j] != '\0'; j++);
		if(aux != NULL){
			aux->adjacentes[j] = v2;
		}
		if(v1 != v2){
			for(i=0; i<100; i++){
				aux = g->elementos[i];
				if((aux == NULL)||(aux->ID == v2)){
					break;
				}
		    	} 
		    	for(j=0; aux != NULL && aux->adjacentes[j] != '\0'; j++);
		    	if(aux != NULL){
		    		aux->adjacentes[j] = v1;
		    	}
		}
	}
}

void imprimirListaAdj(grafo *g){
	int i, j;
	vertice* aux;
	for(i=0; aux != NULL && i < g->vertices; i++){
		aux = g->elementos[i];		
		printf("%c: ", aux->ID);
		j = 0;
		while(aux->adjacentes[j] != '\0'){
			printf("%c ", aux->adjacentes[j]);
			j++;
		}
		printf("\n");	
	}
}


vertice* procurarVertice(grafo *g, char nome){
  vertice* aux;
  for(int i=0; i<100; i++){
	aux = g->elementos[i];    
	if(aux->ID == nome){
      		return aux;
    	}
  }
  return NULL;
}

void DSF(grafo* g, vertice* s){
	printf("A partir do vertice %s:\n", &s->ID);	
	vertice* aux;
	vertice* inicial = s;
	int i = 0;
	int j, k;
	int tempo = 0;
	for(i=0; i<g->vertices; i++){
		g->elementos[i]->cor = 0;
		g->elementos[i]->pai = NULL;
		if(g->elementos[i]->ID == s->ID){
			j = i;
		}
		i++;
	}
	tempo = 0;
	for(k =0; k<g->vertices; k++){
		for(i=0; i<g->vertices; i++){
			for(int w=0; w<g->vertices; w++){
				if(g->elementos[k]->ID == g->elementos[i]->adjacentes[w]){
					g->elementos[i]->cor = 0;				
					DSF_VISIT(g->elementos[i], inicial, g->elementos, tempo, g->vertices);
				}
			}
		}
	}
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
