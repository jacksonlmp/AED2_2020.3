#include <stdio.h>
#include "bst.h"

int main(int argc, char *argv[]){
    no *arvore;
    no *novo;
    

    //Inicialização da Arvore
    arvore = NULL;
    int opcao;

    do{
        novo = NULL;
        scanf("%d", &opcao);
        switch(opcao){
            int chave;
            int valor;
            no *retorno;
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
                retorno = maior(arvore);
                printf("[%d]", retorno->chave);
                break;
            case 6:
                //Menor-Elemento
                retorno = menor(arvore);
                printf("[%d]", retorno->chave);
                break;
            case 7:
                //Altura
                printf("[%d]",altura(arvore));
                break;
            case 8:
                //Quantidade-de-Elementos
                printf("[%d]", quantidade_elementos(arvore));
                break;
            case 9:
                //Busca-de-Elemento
                scanf("%d", &valor);         
                printf("[%d]", existe(arvore, valor));
                break;
            case 10:
                //Antecessor
                novo = inserir(novo, -1);
                scanf("%d", &valor);
                retorno = predecessor(arvore, valor, novo);
                printf("[%d]", retorno->chave);
                break;
            case 11:
                //Sucessor
                novo = inserir(novo, -1);
                scanf("%d", &valor);
                retorno = sucessor(arvore, valor, novo);
                printf("[%d]", retorno->chave);
                break;
            case 12:
                //Remover
                scanf("%d", &valor);
                arvore = remover(arvore, valor);
                break;
            default:
                break;     
        }

    } while(opcao != 99);


}
