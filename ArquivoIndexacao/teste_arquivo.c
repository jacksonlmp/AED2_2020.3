#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

int main(int argc, char * argv[]) {
    int opcao;
	tabela tab;
	inicializarTabela(&tab);

	while(1) {
		scanf("%d", &opcao);
		switch(opcao) {
			int valor;
			case 1:
                adicionarLivro(&tab, ler_dados());
				break;				
			case 2:
				scanf("%d",&valor);
				buscar(valor,tab.indices, &tab);
				break;
			case 3:
				in_order(tab.indices, &tab);
				break;
			case 99:
				finalizar(&tab);
				exit(0);
	    }
	}
}
