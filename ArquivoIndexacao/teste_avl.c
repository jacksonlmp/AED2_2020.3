#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char*argv[]){
    tabela tab;
    arvore a;
    int opcao;
    int controleFB;
    inicializar(&a);
    inicializarTabela(&tab);

    while(1){
        scanf("%d", &opcao);

        switch(opcao){
            int valor;
            case 1:
                adicionarLivro(&tab, ler_dados());
                break;
            case 2:
                tab.indices = carregar_arquivo("dados.dat", tab.indices);
                break;
            case 3:
                salvar_arquivo("dados.dat", tab.indices);
                break;
            case 4:
                imprimir_elemento_arq(a, &tab);
                break;
            case 99:
                finalizar(&tab);
                exit(0);
        }
    }
}
