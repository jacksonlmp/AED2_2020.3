#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;


//Nó duplo preto será usado no Remover
void inicializar(arvore *raiz){
    *raiz = NULL;
    no_null = (arvore) malloc(sizeof(struct no_bst));
    no_null->cor = DUPLO_PRETO;
    no_null->dado = 0;
}

//Valor -> elemento a ser adicionado
//Raiz -> arvore onde o leemnto será adicionado.
//Este parametro é um ponteiro de ponteiro
void adicionar(int valor, arvore *raiz){
    arvore posicao, pai, novo;
    posicao = *raiz;
    pai = NULL;

    while(posicao != NULL){
        pai = posicao;
        if(valor > posicao->dado){
            posicao = posicao->dir;
        }
        else{
            posicao = posicao->esq;
        }
    }
    
    //Achou a posicao, inicializa o novo elemento
    novo = (arvore) malloc(sizeof(struct no_bst));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = pai;
    novo->cor = VERMELHO;

    //Atualiza a raiz da arvore se estiver inserindo o primeiro elemento
    if(eh_raiz(novo)){
        *raiz = novo;
    }
    else{
        //Se nao for raiz, realiza a ligação do pai(direita ou esquerda) como novo elemento
        if(valor > pai->dado){
            pai->dir = novo;
        }
        else{
            pai->esq = novo;
        }
    }
    //Verifica e ajusta a resultante logo após inserir
    ajustar(raiz, novo);    
}

enum cor cor(arvore elemento){
    enum cor c;
    if(elemento == NULL || elemento->cor == PRETO){
        c = PRETO;
    }
    else{
        c = VERMELHO;    
    }
    return c;
}

int eh_raiz(arvore elemento){
    return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento){
    return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

arvore tio(arvore elemento){
    return irmao(elemento->pai);
}

arvore irmao(arvore elemento){
    if(eh_filho_esquerdo(elemento)){
        return elemento->pai->dir;
    }
    else{
        return elemento->pai->esq;
    }
}

void imprimir(arvore raiz){
    printf("(");
    if(raiz != NULL){
        imprimir_elemento(raiz);
        imprimir(raiz->esq);
        imprimir(raiz->dir);
    }
    printf(")");
}

void imprimir_elemento(arvore raiz){
    switch(raiz->cor){
        case PRETO:
            printf("\x1b[30m[%d]\x1b[0m", raiz->dado);
            break;
        case VERMELHO:
            printf("\x1b[31m[%d]\x1b[0m", raiz->dado);
            break;
        case DUPLO_PRETO:
            printf("\x1b[32m[%d]\x1b[0m", raiz->dado);
            break;
    }
}

int altura(arvore raiz){
    if(raiz == NULL){
        return 0;
    }
    return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;    
    }
}

int maior_elemento(arvore raiz){
    if(raiz == NULL){
        return -1;
    }
    if(raiz->dir == NULL){
        return raiz->dado;
    }
    else{
        return maior_elemento(raiz->dir);
    }
}

int menor_elemento(arvore raiz){
    if(raiz == NULL){
        return -1;
    }
    if(raiz->esq == NULL){
        return raiz->dado;
    }
    else{
        return menor_elemento(raiz->esq);    
    }
}

void pre_order(arvore raiz){
    if(raiz != NULL){
        imprimir_elemento(raiz);
        pre_order(raiz->esq);
        pre_order(raiz->dir);
    }
}

void in_order(arvore raiz){
    if(raiz != NULL){
        in_order(raiz->esq);
        imprimir_elemento(raiz);
        in_order(raiz->dir);
    }
}

void pos_order(arvore raiz){
    if(raiz != NULL){
        pos_order(raiz->esq);
        pos_order(raiz->dir);
        imprimir_elemento(raiz);
    }
}

void retira_duplo_preto(arvore *raiz, arvore elemento){
    if(elemento == no_null){
        if(eh_filho_esquerdo){
            elemento->pai->esq = NULL;
        }
        else{
            elemento->pai->dir = NULL;
        }
    }
    else{
        elemento->cor = PRETO;
    }
}

void rotacao_simples_direita(arvore *raiz, arvore pivo){
    arvore u, t1;
    u = pivo->esq;
    t1 = u->dir;

    int posicao_pivo_esq = eh_filho_esquerdo(pivo);
    //Atualiza Ponteiro    
    pivo->esq = t1;

    if(t1 != NULL){
        t1->pai = pivo;
    }
    u->dir = pivo;
    u->pai = pivo->pai;
    pivo->pai = u;

    //Mudança de Cores
    pivo->cor = VERMELHO;
    u->cor = PRETO;

    if(eh_raiz(u)){
        *raiz = u;
    }
    else{
        if(posicao_pivo_esq){
            u->pai->esq = u;
        }
        else{
            u->pai->dir = u;    
        }
    }
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo){
    arvore u, t1;
    u = pivo->dir;
    t1 = u->esq;

    //Rotacao
    pivo->dir = t1;
    
    if(t1 != NULL){
        t1->pai = pivo;
    }

    u->esq = pivo;
    u->pai = pivo->pai;

    if(eh_raiz(pivo)){
        *raiz = u;
    }
    else{
        if(eh_filho_esquerdo(pivo)){
            pivo->pai->esq = u;
        }
        else{
            pivo->pai->dir = u;
        }
    }

    pivo->pai = u;
    u->cor = PRETO;
    pivo->cor = VERMELHO;
}

void ajustar(arvore *raiz, arvore elemento){
    //A Arvore está desajustada se o elemento e seu pai estiverem com a cor vermelha
    while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO){
        
        //Caso 1: Cor do Tio é vermelha, desce o preto do avô
        if(cor(tio(elemento)) == VERMELHO){
            tio(elemento)->cor = PRETO;
            elemento->pai->cor = PRETO;
            elemento->pai->pai->cor = VERMELHO;
            elemento = elemento->pai->pai;
            continue;
        }
        //Caso 2a: Rotacao Simples Direita
        if(eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)){
            rotacao_simples_direita(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->dir->cor = VERMELHO;
            continue;
        }

        //Caso 2b: Rotacao Simples Esquerda
        if(eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)){
            rotacao_simples_esquerda(raiz, elemento->pai->pai);
            elemento->pai->cor = PRETO;
            elemento->pai->esq->cor = VERMELHO;
            continue; 
        }

        //Caso 3a: Rotacao Dupla Direita
        if(!eh_filho_esquerdo(elemento) && eh_filho_esquerdo(elemento->pai)){
            rotacao_simples_esquerda(raiz, elemento->pai);
            rotacao_simples_direita(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->dir->cor = VERMELHO;
            elemento->esq->cor = VERMELHO;         
            continue;
        }

        //Caso 3b: Rotacao Dupla Esquerda
        if(eh_filho_esquerdo(elemento) && !eh_filho_esquerdo(elemento->pai)){
            rotacao_simples_direita(raiz, elemento->pai);
            rotacao_simples_esquerda(raiz, elemento->pai);
            elemento->cor = PRETO;
            elemento->dir->cor = VERMELHO;
            elemento->esq->cor = VERMELHO;            
            continue;
        }
    }

    (*raiz)->cor = PRETO;    

}

void reajustar(arvore *raiz, arvore elemento){
    //Caso 1
    if(eh_raiz(elemento)){
        elemento->cor = PRETO;
        return;
    }

    //Caso 2
    if(irmao(elemento)->dir == NULL || irmao(elemento)->esq == NULL || cor(elemento->pai) == PRETO && cor(irmao(elemento)) == VERMELHO && (cor(irmao(elemento)->dir) == PRETO ) && (cor(irmao(elemento)->esq) == PRETO)){
        if(eh_filho_esquerdo(elemento)){
            rotacao_simples_esquerda(raiz, elemento);
        }
        else{
            rotacao_simples_direita(raiz, elemento);        
        }
        elemento->pai->pai->cor = PRETO;
        elemento->pai->cor = VERMELHO;
        reajustar(raiz, elemento);
        return;
    }

    //Caso 3   
    if(irmao(elemento)->dir == NULL || irmao(elemento)->esq == NULL || cor(elemento->pai) == PRETO && cor(irmao(elemento)) == PRETO && (cor(irmao(elemento)->dir) == PRETO ) && (cor(irmao(elemento)->esq) == PRETO )){
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);
        reajustar(raiz, elemento);
        return;
    }

    //Caso 4
    if(irmao(elemento)->esq == NULL || irmao(elemento) == NULL || irmao(elemento)->dir == NULL || cor(elemento->pai) == VERMELHO && (cor(irmao(elemento)) == PRETO ) && (cor(irmao(elemento)->dir) == PRETO) && (cor(irmao(elemento)->esq)  == PRETO)){
        elemento->pai->cor = PRETO;
        irmao(elemento)->cor = VERMELHO;
        retira_duplo_preto(raiz, elemento);
        return;
    }
    

    //Caso 5a
    if(irmao(elemento)->dir == NULL || eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO &&	(cor(irmao(elemento)->dir) == PRETO) && cor(irmao(elemento)->esq) == VERMELHO){			
			rotacao_simples_direita(raiz, irmao(elemento));
			irmao(elemento)->cor = PRETO;
			irmao(elemento)->dir-> cor = VERMELHO;
			reajustar(raiz, elemento);	
		    return;
	}
    //Caso 5b
    if(irmao(elemento)->esq == NULL || !eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO &&	(cor(irmao(elemento)->esq) == PRETO ) && cor(irmao(elemento)->dir) == VERMELHO){	
			rotacao_simples_esquerda(raiz, irmao(elemento));
			irmao(elemento)->cor = PRETO;
			irmao(elemento)->esq->cor = VERMELHO;
			
			reajustar(raiz, elemento);
		    return;
	}
    //Caso 6a
    if(eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->dir) == VERMELHO){
		enum cor cor_original_pai = cor(elemento -> pai);
		rotacao_simples_esquerda(raiz, elemento -> pai);
		
		elemento->pai->pai->cor = cor_original_pai;
		elemento->pai->cor = PRETO;
		
        tio(elemento)-> cor = PRETO;		
        retira_duplo_preto(raiz, elemento);
		return;
	
	}
    //Caso 6b
    if(!eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO && cor(irmao(elemento)->esq) == VERMELHO){
		enum cor cor_original_pai = cor(elemento -> pai);
		rotacao_simples_direita(raiz, elemento -> pai);
		
		elemento->pai->pai->cor = cor_original_pai;
		elemento->pai->cor = PRETO;
	
    	tio(elemento)->cor = PRETO;		
		retira_duplo_preto(raiz, elemento);
		return;
	
	}
	
}

void remover(int valor, arvore *raiz){
    arvore posicao;
    posicao = *raiz;

    while(posicao != NULL){
        if(valor == posicao->dado){
            //O elemento não possui filhos
            if(posicao->esq == NULL && posicao->dir == NULL){
                //Remover raiz sem filhos
                if(eh_raiz(posicao)){
                    *raiz = NULL;
                    break;
                }
                //Remove elemento que não possui filhos e não é raiz
                //Se for vermelho, apenas remove atualizando o ponteiro
                //Correspondente do pai
                if(posicao->cor == VERMELHO){
                    if(eh_filho_esquerdo(posicao)){
                        posicao->pai->esq = NULL;
                    }
                    else{
                        posicao->pai->dir = NULL;
                    }
                break;
                }
                else{
                    //Se o elemento for preto, substitui pelo duplo preto e ajusta a arvore em seguida
                    no_null->pai = posicao->pai;
                    if(eh_filho_esquerdo(posicao)){
                        posicao->pai->esq = no_null;
                    }
                    else{
                        posicao->pai->dir = no_null;
                    }
                    reajustar(raiz, no_null);
                }
                break;
            }
        }
        //O elemento possui apenas um filho (direito)
        if(posicao->esq == NULL){
            posicao->dir->cor = PRETO;
            if(eh_raiz(posicao)){
                *raiz = posicao->dir;
            }
            else{
                if(eh_filho_esquerdo(posicao)){
                    posicao->pai->esq = posicao->dir;
                }
                else{
                    posicao->pai->dir = posicao->dir;
                }
            }
            break;
        }

        //O elemento possui apenas um filho (esquerdo)
		 if(posicao->dir == NULL) {
			posicao->esq->cor = PRETO;
			if(eh_raiz(posicao)) {
				*raiz = posicao->esq;
			} 
            else {
				if(eh_filho_esquerdo(posicao)) {
					posicao->pai->esq = posicao->esq;
				} 
                else {
					posicao->pai->dir = posicao->esq;
				}
			}
			break;
		}

        //Elemento possui dois filhos
        posicao->dado = maior_elemento(posicao->esq);
        remover(posicao->dado, &posicao->esq);
    }

    if(valor > posicao->dado){
        posicao = posicao->dir;
    }
    else{
        posicao = posicao->esq;
    }

}










