#include <stdio.h>
#include <stdlib.h>
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
        //Elemento menor que raiz relativa, fazer caso simétrico
    }
    return raiz;
}

arvore rotacionar(arvore raiz){
    //FB > 0 => Rotacao esquerda
    if(raiz->fb > 0){
        switch(raiz->dir->fb){
            case 0:             //"Conta" como rotação simples
            case 1:             //Só ocorre no remover
                return rotacao_simples_esquerda(raiz);
            case -1:
                return rotacao_dupla_esquerda(raiz);
        }
    }
    else{
        //Implementar Simétrico
    }
}

//Incluir variável de controle "diminuir" similiar a "cresceu" de adicionar

arvore remover(int valor, arvore raiz){
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
        raiz->esq = remover(raiz->dado, raiz->esq);
        return raiz;
    }
    if(valor > raiz->dado){
        raiz->dir = remover(valor, raiz->dir);
    }
    else{
        raiz->esq = remover(valor, raiz->esq);
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


arvore rotacao_dupla_esquerda(arvore raiz) {
	printf("rotacao dupla esquerda\n");
	return raiz;
}

arvore rotacao_simples_direita(arvore raiz) {
	printf("rotacao simples esquerda\n");
	return raiz;
}
arvore rotacao_dupla_direita(arvore raiz) {
	printf("rotacao dupla direita\n");
	return raiz;
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
        return maior_elemento(raiz->esq);
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












