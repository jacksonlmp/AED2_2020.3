#ifndef BST_H
#define BST_H

typedef struct no{
    int chave;
    struct no *esq;
    struct no *dir;
}no;

no* inserir(no *raiz, int chave); // ok
no* remover(no *raiz, int chave); // ok

no* maior(no *raiz);
no* menor(no *raiz);

no* predecessor(no *raiz, int chave, no* novo);
no* sucessor(no *raiz, int chave, no* novo);

int quantidade_elementos(no *raiz); // ok
int existe(no *raiz, int chave);    //1 ou 0
int altura(no *raiz);               // ok
int MAX(int valorA, int valorB);

void preorder(no *raiz);    //ok
void inorder(no *raiz);     // ok
void posorder(no *raiz);    // ok

#endif
