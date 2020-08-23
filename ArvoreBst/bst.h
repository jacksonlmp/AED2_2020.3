#ifndef BST_H
#define BST_H

typedef struct no{
    int chave;
    struct no *esq;
    struct no *dir;
}no;

no* inserir(no *raiz, int chave);
no* remover(no *raiz, int chave);
no* maiorElemento(no *raiz);
no* menorElemento(no *raiz);
no* predecessor(no *raiz);
no* sucessor(no *raiz);

int quantElementos(no *raiz);
int existe(no *raiz, int chave);    //1 ou 0
int altura(no *raiz);
int MAX(int valorA, int valorB);

void preorder(no *raiz);
void inorder(no *raiz);
void posorder(no *raiz);

#endif
