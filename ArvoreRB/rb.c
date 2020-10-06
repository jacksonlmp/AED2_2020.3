#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

arvore no_null;

void inicializar(arvore *raiz) {
	*raiz = NULL;
	no_null = (arvore) malloc(sizeof(struct no_bst));
	no_null -> cor = DUPLO_PRETO;
	no_null->dado = 0;
}

void adicionar (int valor, arvore *raiz) {
	arvore posicao, pai, novo;

	posicao = *raiz;
	pai = NULL;

	while(posicao != NULL) {
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

	if(eh_raiz(novo))	{
		*raiz = novo;
		novo -> cor = PRETO;
	} 
    else {
		if(valor > pai->dado){
			pai->dir = novo;
        }
		else{
			pai->esq = novo;
        }
	}
	ajustar(raiz, novo);
}

enum cor cor(arvore elemento) {
	enum cor c;
	if(elemento==NULL || elemento->cor == PRETO){
		c = PRETO;
    }
	else{
		c = VERMELHO;
    }
	return c;
}

int eh_raiz(arvore elemento) {
	return (elemento->pai == NULL);
}

int eh_filho_esquerdo(arvore elemento) {
	return (elemento->pai != NULL && elemento == elemento->pai->esq);
}

arvore tio(arvore elemento) {
	return irmao(elemento->pai);
}

arvore irmao(arvore elemento) {
	if(eh_filho_esquerdo(elemento))
		return elemento->pai->dir;
	else
		return elemento->pai->esq;
}

void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

int maior_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

int menor_elemento(arvore raiz) {
	if(raiz == NULL)
			return -1;
	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz) {
	if(raiz != NULL) {
		imprimir_elemento(raiz);
		pre_order(raiz->esq);
		pre_order(raiz->dir);
	}
}

void pos_order(arvore raiz) {
	if(raiz != NULL) {
		pos_order(raiz->esq);
		pos_order(raiz->dir);
		imprimir_elemento(raiz);
	}
}

void in_order(arvore raiz) {
	if(raiz != NULL) {
		in_order(raiz->esq);
		imprimir_elemento(raiz);
		in_order(raiz->dir);
	}
}

void imprimir_elemento(arvore raiz) {
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

void retira_duplo_preto(arvore *raiz, arvore elemento) {
	if(elemento == no_null)
		if(eh_filho_esquerdo(elemento)){
			elemento->pai->esq = NULL;
        }
		else{
			elemento->pai->dir = NULL;
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
	pivo->esq = t1;

    if(t1 != NULL){
        t1->pai = pivo;
    }

	u->dir = pivo;    
	u->pai = pivo->pai;
	pivo->pai = u;

    pivo->cor = VERMELHO;
	u->cor = PRETO;

	if(eh_raiz(u))
		*raiz = u;
	else{
	    if(posicao_pivo_esq){
	    	u->pai->esq = u;
		} 
        else {
    		u->pai->dir = u;
		}
	}
}

void rotacao_simples_esquerda(arvore *raiz, arvore pivo) {
	arvore u, t1;
	u = pivo -> dir;
    t1 = u -> esq;

	int posicao_pivo_esq = eh_filho_esquerdo(pivo);
	pivo -> dir = t1;

    if(t1 != NULL){
		t1->pai = pivo;
	}

	u -> esq = pivo;
	u -> pai = pivo -> pai;
	pivo -> pai = u;

    pivo -> cor = VERMELHO;
	u -> cor = PRETO;

	if(eh_raiz(u))
		*raiz = u;
	else {
		if(posicao_pivo_esq){
			u->pai->esq = u;
		} 
        else {
			u->pai->dir = u;
		}
	}
}

void remover(int valor, arvore *raiz){
	arvore posicao;
	posicao = *raiz;	
	while(posicao != NULL) {
		if(valor == posicao->dado) {
			// 0 filhos
			if(posicao->esq == NULL && posicao->dir == NULL) {					
				//Remover raiz sem filhos					
				if(eh_raiz(posicao)) {
					*raiz = NULL;
					break;
				}
				
				if(posicao->cor == VERMELHO) {
						if(eh_filho_esquerdo(posicao)){
							posicao->pai->esq = NULL;
						} else {
							posicao->pai->dir = NULL;
						}
				break;			    
                } 
                else {							
					no_null -> pai = posicao -> pai;
					
					if(eh_filho_esquerdo(posicao)){
						posicao -> pai -> esq = no_null;
					} 
                    else {
						posicao -> pai -> dir = no_null;
					}
					
					reajustar(raiz, no_null);
					break;						
				} 
			} 
		// apenas o filho esquerdo
		if(posicao -> dir == NULL){
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
			
		// apenas o filho direito
		if(posicao -> esq == NULL){
					posicao->dir->cor = PRETO;
					if(eh_raiz(posicao)) {
						*raiz = posicao->dir;
					} 
                    else {
						if(eh_filho_esquerdo(posicao)) {
							posicao->pai->esq = posicao->dir;
						} 
                        else {
							posicao->pai->dir = posicao->dir;
						}
					}
					break;
			}
			
		// 2 filhos
		if(posicao -> dir != NULL && posicao -> esq != NULL){
				posicao->dado = maior_elemento(posicao->esq);
				remover(posicao->dado, &(posicao->esq));
				break;
		}	
	} 	
			if(valor > posicao -> dado){
				posicao = posicao -> dir;
			} 
            else {
				posicao = posicao -> esq;
			}	 	
	} 	
}

void ajustar(arvore *raiz, arvore elemento){
	while(cor(elemento->pai) == VERMELHO && cor(elemento) == VERMELHO) {
			//Caso 1
			if(cor(tio(elemento)) == VERMELHO) {
				tio(elemento)->cor = PRETO;
				elemento->pai->cor = PRETO;
				elemento->pai->pai->cor = VERMELHO;
				elemento = elemento->pai->pai;
				continue;
			} 

			//Caso 2
			if(eh_filho_esquerdo(elemento) &&
             eh_filho_esquerdo(elemento->pai)) {
				rotacao_simples_direita(raiz, elemento->pai->pai);
				elemento->pai->cor = PRETO;
				elemento->pai->dir->cor = VERMELHO;
				continue;
			}

			//Caso 2b
			if(!eh_filho_esquerdo(elemento) &&
             !eh_filho_esquerdo(elemento->pai)) {
				rotacao_simples_esquerda(raiz, elemento->pai->pai);
				elemento->pai->cor = PRETO;
				elemento->pai->esq->cor = VERMELHO;
			    continue;
			}

			//Caso 3a
			if(!eh_filho_esquerdo(elemento) && 
             eh_filho_esquerdo(elemento->pai)) {
			  rotacao_simples_esquerda(raiz, elemento->pai);
				rotacao_simples_direita(raiz, elemento -> pai);
				elemento->cor = PRETO;
				elemento->dir->cor = VERMELHO;
				elemento->esq->cor = VERMELHO;
				continue;
			}
					
			//Caso 3b
			if(eh_filho_esquerdo(elemento) && 
            !eh_filho_esquerdo(elemento->pai)) {
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
	if(cor(elemento->pai) == PRETO &&
	 cor(irmao(elemento)) == VERMELHO &&
	 (cor(irmao(elemento)->dir) == PRETO || irmao(elemento)->dir == NULL) &&
	 (cor(irmao(elemento)->esq) == PRETO || irmao(elemento)->esq == NULL)) {

		if(eh_filho_esquerdo(elemento)){
			rotacao_simples_esquerda(raiz, elemento->pai);
		} 
        else {
			rotacao_simples_direita(raiz, elemento->pai);
		}	
		elemento->pai->pai->cor = PRETO;
		elemento->pai->cor = VERMELHO;
        reajustar(raiz, elemento);
		return;
	}
	
	//Caso 3
	if(cor(elemento->pai) == PRETO && cor(irmao(elemento)) == PRETO &&
	(cor(irmao(elemento)->dir)  == PRETO || irmao(elemento)->dir == NULL) && 
    (cor(irmao(elemento)->esq)  == PRETO || irmao(elemento)->esq == NULL)){	
	    irmao(elemento)->cor = VERMELHO;
	    retira_duplo_preto(raiz, elemento);
	    reajustar(raiz, elemento->pai);	
	    return;
	}
	
	//Caso 4
	if(cor(elemento->pai) == VERMELHO && 
	(cor(irmao(elemento)) == PRETO || irmao(elemento) == NULL) &&
	(cor(irmao(elemento)->dir) == PRETO || irmao(elemento)->dir == NULL) && 
    (cor(irmao(elemento)->esq) == PRETO || irmao(elemento)->esq == NULL)){
		elemento->pai->cor = PRETO;
		irmao(elemento)->cor = VERMELHO;
		retira_duplo_preto(raiz, elemento); 
		return;
	}

	//Caso 5a
	if(eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO &&
	(cor(irmao(elemento)->dir) == PRETO || irmao(elemento)->dir == NULL) && 
     cor(irmao(elemento)->esq) == VERMELHO){		
		rotacao_simples_direita(raiz, irmao(elemento));
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->dir->cor = VERMELHO;
		reajustar(raiz, elemento);	
	    return;
	}
	
	//Caso 5b
	if(!eh_filho_esquerdo(elemento) && cor(irmao(elemento)) == PRETO &&
	(cor(irmao(elemento)->esq) == PRETO || irmao(elemento)->esq == NULL) && 
     cor(irmao(elemento)->dir) == VERMELHO){		
		rotacao_simples_esquerda(raiz, irmao(elemento));
		irmao(elemento)->cor = PRETO;
		irmao(elemento)->esq->cor = VERMELHO;
		reajustar(raiz, elemento);
	    return;
	}
	
	//Caso 6a
	if(eh_filho_esquerdo(elemento) && 
		cor(irmao(elemento)) == PRETO && 
		cor(irmao(elemento) -> dir) == VERMELHO){	
		enum cor cor_original_pai = cor(elemento -> pai);
		
		rotacao_simples_esquerda(raiz, elemento -> pai);	
		elemento->pai->pai->cor = cor_original_pai;
		elemento->pai->cor = PRETO;
		tio(elemento)->cor = PRETO;	
		retira_duplo_preto(raiz, elemento);
		return;
	}
    
    //Caso 6b	
	if(!eh_filho_esquerdo(elemento) && 
		cor(irmao(elemento)) == PRETO && 
		cor(irmao(elemento)->esq) == VERMELHO){
		enum cor cor_original_pai = cor(elemento->pai);
		
		rotacao_simples_direita(raiz, elemento->pai);	
		elemento->pai->pai->cor = cor_original_pai;
		elemento->pai->cor = PRETO;
		tio(elemento)->cor = PRETO;		
		retira_duplo_preto(raiz, elemento);
		return;
	}
}

