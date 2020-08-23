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
                scanf("%d", &chave);
                arvore = inserir(arvore, chave);
                break;
            case 2:
                preorder(arvore);  
                break;
            case 3:
                inorder(arvore);
                break;
            case 4:
                posorder(arvore);
                break;
            case 5:
                maiorElemento(arvore);
                break;
            case 6:
                menorElemento(arvore);
                break;
            case 7:
                printf("[%d]",altura(arvore));
                break;
            case 8:
                scanf("%d", &valor);
                existe(arvore, valor);
                break;
    
            default:
                break;     
        }

    } while(opcao != 99);


}
