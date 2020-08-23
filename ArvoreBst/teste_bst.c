#include <stdio.h>
#include "bst.h"

int main(int argc, char *argv[]){
    no *arvore;

    //Inicialização da Arvore
    arvore = NULL;
    int opcao;

    do{
        scanf("%d", &opcao);
        switch(opcao){
            int chave;
            int valor;
            case 1:
                //Inserir           
                scanf("%d", &chave);
                arvore = inserir(arvore, chave);
                break;
            case 2:
                //Pre-Order
                preorder(arvore);  
                break;
            case 3:
                //In-Order
                inorder(arvore);
                break;
            case 4:
                //Pos-Order
                posorder(arvore);
                break;
            case 5:
                //Maior-Elemento
                maiorElemento(arvore);
                break;
            case 6:
                //Menor-Elemento
                menorElemento(arvore);
                break;
            case 7:
                //Altura
                printf("[%d]",altura(arvore));
                break;
            case 8:
                //Quantidade-de-Elementos
                printf("[%d]", quantElementos(arvore));
                break;
            case 9:
                //Antecessor
                break;
            case 10:
                //Sucessor
                break;
            case 11:
                //Remover
            default:
                break;     
        }

    } while(opcao != 99);


}
