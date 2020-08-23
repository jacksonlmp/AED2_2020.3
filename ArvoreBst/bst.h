#ifndef BST_H
#define BST_H

typedef struct no{
    int chave;
    struct no *esq;
    struct no *dir;
}no;

no* inserir(no *raiz, int chave);
no* remover(no *raiz, int chave);
no* maior(no *raiz);
no* menor(no *raiz);
no* predecessor(no *raiz);
no* sucessor(no *raiz);
int quantidade_elementos(no *raiz);
int existe(no *raiz, chave);    //1 ou 0

void preorder(no *raiz);
void inorder(no *raiz);
void posorder(no *raiz);

#endif
