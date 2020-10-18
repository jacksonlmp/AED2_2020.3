#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "arquivo.h"

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

arvore adicionar (tipo_dado *valor, arvore raiz, int *cresceu) {
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
	    *cresceu = 1; 
		return novo;
	}
	if(valor->chave > raiz->dado->chave) {
		raiz->dir = adicionar(valor, raiz->dir, cresceu);
        if(*cresceu) {
			switch(raiz->fb) {
				case 0:
					raiz->fb = 1;
                    *cresceu = 1;
					break;
			    case -1:
					raiz->fb = 0;
					*cresceu = 0;
					break;
				case 1:
					*cresceu = 0;
					return rotacionar(raiz);
			}
		}
	} 
    else {
	   raiz->esq = adicionar(valor,raiz->esq,cresceu);
	   if(*cresceu){
		   switch(raiz->fb){
			   case 0:
			   		raiz->fb = -1;
					*cresceu = 1;
					break;
			   case -1:
					*cresceu = 0;
					return rotacionar(raiz);
					break;
			   case 1:
			   		raiz->fb = 0;
					*cresceu = 0;
					break;
		   }
	   }
	}
	return raiz;
}

//---------------------------------------------------ROTAÇÕES
arvore rotacionar(arvore raiz) {
	if(raiz->fb > 0){
        switch(raiz->dir->fb){
            case 0:         
                return rotacao_simples_esquerda(raiz);
                break;   
            case 1:             
                return rotacao_simples_esquerda(raiz);
                break;
            case -1:
                return rotacao_dupla_esquerda(raiz);
                break;
        }
    }
    else{
        switch(raiz->esq->fb){
            case 0:
                return rotacao_simples_direita(raiz);
                break;
            case 1:
                return rotacao_dupla_direita(raiz);
                break;
            case -1:
                return rotacao_simples_direita(raiz);
                break;
        }
    }
}

arvore rotacao_simples_esquerda(arvore raiz) {
	arvore p, u, t1, t2, t3;
    //Inicializa os ponteiros
    p = raiz;
    u = raiz->dir;
    t1 = p->esq;

    //t2 e t3 não estãõ sendo modificados
    t2 = u->esq;
    t3 = u->dir;

    //Atualiza os ponteiros
    p->dir = t1;
    u->esq = p;

    //Atualiza os fbs de acordo com o fb de u
    if(u->fb == 1){
        p->fb = 0;
        u->fb = 0;
    }
    else{
        p->fb = 1;
        u->fb = -1;
    }
    //Raiz da sub-arvore resultante
    return u;
}

arvore rotacao_simples_direita(arvore raiz) {
	arvore u, t2, p;

    u = p->esq;
    t2 = u->dir;

    //Atualiza os Ponteiros
    p->esq = t2;
    u->dir = p;

    if(u->fb ==0){
        p->fb = -1;
        u->fb = 1;
    }
    else{
        p->fb = 0;
        u->fb = 0;
    }
    return u;
}

arvore rotacao_dupla_esquerda(arvore raiz) {
	arvore u, v, p, t2, t3;

    u = p->dir;
    v = u->esq;

    t2 = v->esq;
    t3 = v->dir;

    u->esq = t3;
    v->dir = u;
    p->dir = v;

    p->dir = t2;
    v->esq = p;

    switch(v->fb){
        case 0:
            p->fb = 0;
            u->fb = 0;
            break;
        case 1:
            u->fb = 0;
            p->fb = -1;
            v->fb = 0;
            break;
        case -1:
            u->fb = 1;
            p->fb = 0;
            v->fb = 0;
            break;
    }
    return v;
}


arvore rotacao_dupla_direita(arvore raiz) {
	arvore u, v, p, t2, t3;

    u = p->esq;
    v = u->dir;

    t2 = v->esq;
    t3 = v->dir;

    u->dir = t2;
    v->esq = u;
    p->esq = v;

    p->esq = t3;
    v->dir = p;

    switch(v->fb){
        case 0:
            u->fb = 0;
            p->fb = 0;
            break;
        case 1:
            u->fb = -1;
            p->fb = 0;
            v->fb = 0;
            break;
        case -1:
            u->fb = 0;
            p->fb = 1;
            v->fb = 0;
            break;
    }
    return v;
}

//----------------------------------------------------
int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b){
		return a;
    }
	else{
		return b;
    }
}

tipo_dado *maior_elemento(arvore raiz) {
	if(raiz == NULL){
		return NULL;
    }
	if(raiz->dir == NULL){
		return raiz->dado;
    }
	else{
		return maior_elemento(raiz->dir);
    }
}

tipo_dado *menor_elemento(arvore raiz) {
	if(raiz == NULL){
		return NULL;
    }
	if(raiz->esq == NULL){
		return raiz->dado;
    }
	else{
		return maior_elemento(raiz->esq);
    }
}

void pre_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento(raiz, tab);
		pre_order(raiz->esq, tab);
		pre_order(raiz->dir, tab);
	}
}

void in_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order(raiz->esq, tab);
		imprimir_elemento(raiz, tab);
		in_order(raiz->dir, tab);
	}
}

void pos_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order(raiz->esq, tab);
		pos_order(raiz->dir, tab);
		imprimir_elemento(raiz, tab);
	}
}

//----------------------------------------------ARQUIVO
int inicializarTabela(tabela *tab) {
	inicializar(&tab->indices);	
	tab->arquivo_dados = fopen("dados.dat", "a+");
	tab->indices = carregar_arquivo("indices.dat", tab->indices);
	if(tab->arquivo_dados != NULL){
		return 1;
    }
	else{
		return 0;
    }
}

void imprimir_elemento(arvore raiz, tabela * tab) {
	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);

	char * buffer = (char *) malloc(256 * sizeof(char));
	char *aux;

	fscanf(tab->arquivo_dados," %[^\n]s",buffer); 
	aux = strtok(buffer,"|"); 

	while(aux != NULL){ 
		printf("%s",aux);
		aux = strtok(NULL,"|");
		if(aux != NULL){
			printf(",");
		}
	}
	printf("\n");
	free(buffer);
	free(aux);
}

dado * ler_dados() {
	dado *novo = (dado *) malloc(sizeof(dado));
	char *buffer = (char *) malloc(256 * sizeof(char));

	getchar() ;
	printf("Titulo: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	novo->titulo = strdup(buffer);

	printf("Autor: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	novo->autor = strdup(buffer);

	printf("Isbn: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
	novo->isbn = strdup(buffer);

	printf("Codigo: ");
	scanf("%d", &novo->codigo);
	free(buffer);

	return novo;
}

void tirar_enter(char *string) {
	string[strlen(string) -1] = '\0';
}

void salvar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "wb");
	if(arq != NULL) {
		salvar_auxiliar(a, arq);
	}
	fclose(arq);
}

void salvar_auxiliar(arvore raiz, FILE *arq){
	if(raiz != NULL) {
		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}
}

arvore carregar_arquivo(char *nome, arvore a) {
	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado * temp;
	int cresceu;
	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) { 
			a = adicionar(temp, a,&cresceu);			
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		}
		fclose(arq);
	}
	return a;
}

void finalizar (tabela *tab) {
	fclose(tab->arquivo_dados);
	salvar_arquivo("indices.dat", tab->indices);
}

void adicionarLivro(tabela *tab, dado *livro){
	if(tab->arquivo_dados != NULL) {
		int cresceu;
		fseek(tab->arquivo_dados, 0L, SEEK_END);
		tipo_dado * novo = (tipo_dado *) malloc(sizeof(tipo_dado));

		novo->chave = livro->codigo;
		novo->indice = ftell(tab->arquivo_dados);

		fprintf(tab->arquivo_dados,"%d|%s|%s|%s\n",livro->codigo,livro->titulo,livro->autor,livro->isbn);
		tab->indices = adicionar(novo, tab->indices,&cresceu);			
	}
}

void buscar(int valor,arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		buscar(valor,raiz->esq, tab);
		if(valor == raiz->dado->chave){
			imprimir_elemento(raiz, tab);
		}
		buscar(valor,raiz->dir, tab);
	}
}
