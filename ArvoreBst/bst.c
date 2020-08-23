#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

no* inserir(no *raiz, int chave){
    //Caso Base
    if(raiz == NULL){
        no *novo;

        //Passo 1 - Alocar Memoria
        novo = (no*)malloc(sizeof(no));

        //Passo 2 - Inicializar Valores
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;

        //Passo 3 - Retornar o ponteiro para o nó que foi criado
        return novo;  
    }
    else{
        //Verificar se o valor deve ser inserido na esquerda (<) ou direita (>)
        if(chave > raiz->chave){
            raiz->dir = inserir(raiz->dir, chave);
        }
        else{
            raiz->esq = inserir(raiz->esq, chave);
        }
        return raiz;
    }
}

void preorder(no *raiz){
    if(raiz != NULL){
        printf("[%d]", raiz->chave);
        preorder(raiz->esq);
        preorder(raiz->dir);
    }
}

void inorder(no *raiz){
    if(raiz != NULL){
        inorder(raiz->esq);
        printf("[%d]", raiz->chave);
        inorder(raiz->dir);
    }
}

void posorder(no *raiz){
    if(raiz != NULL){
        posorder(raiz->esq);
        posorder(raiz->dir);
        printf("[%d]", raiz->chave);
    }
}

no* maiorElemento(no *raiz){
    while(raiz->dir != NULL){
        raiz = raiz->dir;
    }
    printf("[%d]", raiz->chave);
}


no* menorElemento(no *raiz){
    while(raiz->esq != NULL){
        raiz = raiz->esq;
    }
    printf("[%d]", raiz->chave);
}

int MAX(int valorA, int valorB){
    if(valorA > valorB){
        return valorA;
    }
    else{
        return valorB;    
    }
}

int altura(no* raiz){
    if(raiz == NULL){
        return 0;    
    }
    return 1 + MAX(altura(raiz->esq), altura(raiz->dir));
}

int existe(no *raiz, int chave){
    if(raiz != NULL){
        if(raiz->chave == chave){
            return raiz;
        }
        else{
            if(chave > raiz->chave){
                return existe(raiz->dir, chave);            
            }
            else{
                return existe(raiz->esq, chave);
            }    
        }
    }
    return NULL;
}













