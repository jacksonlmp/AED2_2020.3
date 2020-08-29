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
                //Remover
                scanf("%d", &valor);
                arvore = remover(arvore, valor);
                break;                
           
            case 6:
                //Maior-Elemento
                retorno = maior(arvore);
                printf("[%d]", retorno->chave);
                break;
                
            case 7:
                //Menor-Elemento
                retorno = menor(arvore);
                printf("[%d]", retorno->chave);
                break;
                
            case 8:
                //Altura
                printf("[%d]",altura(arvore));
                break;
                
            case 9:
                //Quantidade-de-Elementos
                printf("[%d]", quantidade_elementos(arvore));
                break;
                               
            case 10:
                //Busca-de-Elemento
                scanf("%d", &valor);         
                printf("[%d]", existe(arvore, valor));
                break;
           
            case 11:
                //Predecessor
                novo = inserir(novo, -1);
                scanf("%d", &valor);
                retorno = predecessor(arvore, valor, novo);
                printf("[%d]", retorno->chave);
                break;
                
            case 12:
                //Sucessor
                novo = inserir(novo, -1);
                scanf("%d", &valor);
                retorno = sucessor(arvore, valor, novo);
                printf("[%d]", retorno->chave);
                break;
                 
            default:
                break;     
        }

    } while(opcao != 99);


}
