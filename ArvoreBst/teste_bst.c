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
            case 1:           
                scanf("%d", &chave);
                arvore = inserir(arvore, chave);
                break;
            case 2:
                preorder(arvore);  
                break;
            default:
                break;     
        }

    } while(opcao != 99);


}
