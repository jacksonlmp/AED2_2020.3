#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

void inicializar(arvore *raiz){
    *raiz = NULL;
}

//Valor - Elemento a ser inserido
//Raiz - Raiz da arvore onde o elemento será inserido
//Cresceu - Variavel de controle que ajuda calcular o Fator de Balanço

arvore adicionar (int valor, arvore raiz, int *cresceu){
    //Caso base - árvore vazia ou folha
    if(raiz == NULL){
        arvore novo = (arvore) malloc(sizeof(struct no_avl));
        novo->dado = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        *cresceu = 1;
        return novo;
    }

    if(valor > raiz->dado){
        raiz->dir = adicionar(valor, raiz->dir, cresceu);
        
        //Atualização do FB sem calculo_altura
        if(*cresceu){
            switch(raiz->fb){
                case 0:
                    raiz->fb = 1;
                    *cresceu = 1;
                    break;
                case -1:
                    raiz->fb = 0;
                    cresceu = 0;
                    break;
                case 1:
                    cresceu = 0;
                    return rotacionar(raiz);
            }    
        }
        
    }
    else{
        raiz->esq = adicionar(valor, raiz->esq, cresceu);
        if(*cresceu){
            switch(raiz->fb){
                case 0:
                    raiz->fb = -1;
                    *cresceu = 1;
                    break;
                case -1:
                    raiz->fb = -2;
                    *cresceu = 0;
                    return rotacionar(raiz);
                case 1:
                    raiz->fb = 0;
                    cresceu = 0;
                    break;
            }
        }
    }
    return raiz;
}

arvore rotacionar(arvore raiz){
    //FB > 0 => Rotacao esquerda
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

//Incluir variável de controle "diminuir" similiar a "cresceu" de adicionar

arvore remover(int valor, arvore raiz, int *diminuiu){
    if(raiz == NULL){
        return NULL;
    }

    if(raiz->dado == valor){
        if(raiz->esq == NULL){
            return raiz->dir;
        }
        if(raiz->dir == NULL){
            return raiz->esq;
        }
        raiz->dado = maior_elemento(raiz->esq);
        raiz->esq = remover(raiz->dado, raiz->esq, diminuiu);
        return raiz;
    }
    if(valor > raiz->dado){
        raiz->dir = remover(valor, raiz->dir, diminuiu);
        if(*diminuiu){
            switch(raiz->fb){
                case 0:
                    raiz->fb = -1;
                    *diminuiu = 0;
                    break;
                case 1:
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
                case -1:
                    if(raiz->esq->fb == 0){
                        *diminuiu = 0;                    
                    }
                    else{
                        *diminuiu = 1;        
                    }
                    return rotacionar(raiz);
                    break;
            }
        }        
    }
    else{
        raiz->esq = remover(valor, raiz->esq, diminuiu);
        if(*diminuiu){
            switch(raiz->fb){
                case 0:
                    raiz->fb = 1;
                    *diminuiu = 0;
                    break;
                case 1:
                    if(raiz->dir->fb == 0){
                        *diminuiu = 0;    
                    }
                    else{
                        *diminuiu = 1;                    
                    }
                    return rotacionar(raiz);
                    break;
                case -1:
                    raiz->fb = 0;
                    *diminuiu = 1;
                    break;
            }
        }
    }
    return raiz;
}

arvore rotacao_simples_esquerda(arvore raiz){
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

void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

void imprimir_elemento(arvore raiz){
    printf("%d [%d]", raiz->dado, raiz->fb);
}

int altura(arvore raiz){
    if(raiz == NULL){
        return 0;
    }
    return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}

int maior_elemento(arvore raiz){
    if(raiz == NULL){
        return -1;
    }
    if(raiz->dir == NULL){
        return raiz->dado;
    }
    else{
        return maior_elemento(raiz->dir);
    }
}

int menor_elemento(arvore raiz){
    if(raiz == NULL){
        return -1;
    }
    if(raiz->esq == NULL){
        return raiz->dado;
    }
    else{
        return menor_elemento(raiz->esq);
    }
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

tipo_dado * ler_dados() {
	tipo_dado *novo = (tipo_dado *) malloc(sizeof(tipo_dado));
	char * buffer = (char *) malloc(256 * sizeof(char));

	getchar() ;
	printf("Titulo: ");
	fgets(buffer, 255,  stdin);
	tirar_enter(buffer);
/*	novo->titulo = (char *) malloc ((strlen(buffer) + 1) * sizeof(char));
	strcpy(novo->titulo, buffer);*/
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
		fclose(arq);
	}
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

	if(arq != NULL) {
		temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		while(fread(temp, sizeof(tipo_dado), 1, arq)) {			
			a = adicionar(temp, a, cresceu);			
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));

		}
		fclose(arq);
	}
	return a;
}














