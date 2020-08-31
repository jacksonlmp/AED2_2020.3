#ifndef AVL_H
#define AVL_H

typedef int tipo_dado;

typedef struct no_avl{
    tipo_dado dado;
    int fb;
    struct no avl *esq, *dir;
} no_avl;

