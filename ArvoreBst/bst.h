#ifndef BST_H
#define BST_H

typedef struct no{
    int chave;
    struct no *esq;
    struct no *dir;
}no;

no* inserir(no *raiz, int chave);
no* remover(no *raiz, int chave);

int maior(no *raiz);
int menor(no *raiz);

int predecessor(no *raiz, int chave, no* novo);
int sucessor(no *raiz, int chave, no* novo);

int quantidade_elementos(no *raiz);
int existe(no *raiz, int chave);    //1 ou 0
int altura(no *raiz);
int MAX(int valorA, int valorB);

void preorder(no *raiz);
void inorder(no *raiz);
void posorder(no *raiz);

#endif
