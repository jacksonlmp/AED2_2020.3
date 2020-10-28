#include <iostream>
#include <set>
#include <iterator>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include "kruskal.h"

using namespace std;

Lista *inicializaL(void){
    return NULL;
}

Vertice *inicializaV(void){
    return NULL;
}

Grafo *inicializaG(void){
    return NULL;
}

Conjunto *inicializaC(void){
    return NULL;
}

Aresta *inicializaA(void){
    return NULL;
}

MST *inicializaM(void){
    return NULL;
}

Grafo *insere_Vertices(Grafo *grafo, Vertice *vertices, Aresta *arestas){
    grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->vertices = vertices;
    grafo->arestas = arestas;
    return grafo;
}

MST *insere_MST(MST *arv, Aresta *a){
   MST *novo = (MST*)malloc(sizeof(MST));
   novo->aresta = a;

   if(arv == NULL){
        novo->prox = arv;
        return novo;
   }
    else{
        MST *p;
        p = arv;
        while(p->prox != NULL){
            p = p->prox;
        }
        novo->prox = NULL;
        p->prox = novo;
    }
    return arv;
}

Aresta *insere_crescenteAresta(Aresta *aresta, Vertice *v, Vertice *u, int peso){
    if(v == NULL || u == NULL){
        return NULL;
    }

    Aresta *novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->v = v;
    novaAresta->u = u;
    novaAresta->peso = peso;

    if(aresta == NULL || aresta->peso >= peso){
        novaAresta->prox = aresta;
        return novaAresta;
    }
    Aresta *p = aresta, *ant = aresta;
    while(p->prox != NULL && p->peso <= peso){
        ant = p;
        p = p->prox;
    }
    if(p->prox == NULL){
        p->prox = novaAresta;
        novaAresta->prox =  NULL;
    }
    else{
        ant->prox = novaAresta;
        novaAresta->prox = p;
    }
    return aresta;
}

Vertice *insere_inicioVertice(Vertice *v, char letra){
    Vertice *novo = (Vertice*)malloc(sizeof(Vertice));
    novo->letra[0] = letra;
    novo->proxElemento = NULL;

    if(v == NULL){
        novo->prox = v;
        return novo;
    }
    else{
        Vertice *p;
        p = v;
        while(p->prox != NULL){
            p = p->prox;
        }
        novo->prox = NULL;
        p->prox = novo;
    }
    return v;
}

Lista *insere_inicioLista(Lista *l, Vertice *v){
    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->vertice = v;

    if(l == NULL){
        novo->prox = l;
        return novo;
    }
    else{
        Lista *p;
        p = l;
        while(p->prox != NULL){
            p = p->prox;
        }
        novo->prox = NULL;
        p->prox = novo;
    }
    return l;
}

void imprimirLista(Lista *l){
    Lista *p;

    for(p = l; p != NULL; p = p->prox){
        std::cout << p->vertice->letra[0] << " ";
    }
    std::cout << "\n";
}

void imprimirConjunto(Conjunto *l){
    Conjunto *p;

    for(p = l; p != NULL; p = p->prox){
        imprimirLista(p->lista) ;
    }
}

void imprimirMST(MST *l){
    MST *p;
    std::cout << "MST" << std::endl;

    for(p = l; p != NULL; p = p->prox){
        std::cout  << "(" << p->aresta->v->letra[0] << ", " <<p->aresta->u->letra[0] << ")  peso = " << p->aresta->peso << std::endl;
    }
}

void imprimirArestas(Aresta *l){
    Aresta *p;

    for(p = l; p != NULL; p = p->prox){
        std::cout << p->v->letra[0] << p->u->letra[0] << " " << p->peso << std::endl;
    }
}

void imprimir(Vertice *v){
    Vertice *p;

    for(p = v; p != NULL; p = p->prox){
        std::cout << p->letra[0] << ": ";
        imprimirLista(p->proxElemento);
    }
}

Vertice *retornaVertice(Vertice *v, char letra){
    Vertice *temp;
    temp = v;

    if(temp == NULL){
        return NULL;
    }
    while(temp != NULL){
        if(temp->letra[0] == letra){
            return temp;
        }
        temp = temp->prox;
    }
    return NULL;
}

Grafo *abrirArquivo(Grafo *grafo, int direcional){
    int i, j, k;
    char a[1000];
    char vertices[1000];
    char arestas[1000];
    FILE *fp;
    j = 0;
    fp = fopen("entrada.txt", "r");

    if(fp != NULL) {
        if(fgets(a, 1000, fp)!= NULL)
        for(k = 0; k < strlen(a); k++){
            if(a[k] == ' '){
                vertices[k] = '\0';
                break;
            }
            vertices[k] = a[k];

        }
        for(k = k+1; k < strlen(a)-1; k++){
            arestas[j] = a[k];
            j += 1;
        }
        arestas[j] = '\0';
        fclose(fp);
    }
    int vert = atoi(vertices);
    int arest = atoi(arestas);

	char a_[1000];
    char vertices_[vert+1];
    char arestas_[2*arest+1];
    char w[1000];
    int peso;

    Aresta *Arestas = inicializaA();
    Vertice *Vertices = inicializaV();;

    fp = fopen("entrada.txt", "r");

	if(fp != NULL) {
        for(k = 0; k < vert+1; k++){
            if(fgets(a_, 1000, fp)!= NULL){
                if(k > 0){
                    vertices_[k-1] = a_[0];
                }
            }
        }
        vertices[k-1] = '\0';

        i = 0;
        while(i < vert){
            Vertices = insere_inicioVertice(Vertices, vertices_[i]);
            i += 1;
        }

        for(k = 0; k < arest+1; k++){
            if(fgets(a_, 1000, fp)!= NULL){
                arestas_[2*k] = a_[0];
                arestas_[2*k+1] = a_[1];
                int v;
                for(v = 3; v < strlen(a_); v++){
                    w[v-3] = a_[v];
                }
                peso = atoi(w);
                Vertice *c;
                Vertice *d;
                c = retornaVertice(Vertices, arestas_[2*k]);
                d = retornaVertice(Vertices, arestas_[2*k+1]);
                Arestas = insere_crescenteAresta(Arestas, c, d, peso);
            }
        }
        arestas_[2*k-2] = '\0';
        fclose(fp);
    }
    for(i = 0; i < strlen(arestas_); i++){
        Vertice *temp;
        Vertice *t;
        temp = retornaVertice(Vertices, arestas_[i]);
        if(i % 2 == 0){
                t = retornaVertice(Vertices, arestas_[i+1]);
                temp->proxElemento = insere_inicioLista(temp->proxElemento, t);
        }
        else{
                if(direcional == 0){
                    t = retornaVertice(Vertices, arestas_[i-1]);
                    temp->proxElemento = insere_inicioLista(temp->proxElemento, t);
                }
        }
    }
    grafo = insere_Vertices(grafo, Vertices, Arestas);
    return grafo;
}

Conjunto *MAKE_SET(Vertice *v, Conjunto *W){
    Conjunto *novo = (Conjunto*)malloc(sizeof(Conjunto));
    novo->lista = inicializaL();
    novo->lista = insere_inicioLista(novo->lista, v);
    novo->tamanho = 1;

    if(W == NULL){
        novo->prox = W;
        return novo;
    }
    else{
        Conjunto *p;
        p = W;
        while(p->prox != NULL){
            p = p->prox;
        }
        novo->prox = NULL;
        p->prox = novo;
    }
    return W;
}

Conjunto *FIND_SET(Vertice *v, Conjunto *W){
    Conjunto *p;

    for(p = W; p != NULL; p = p->prox){
        Lista *l;
        for(l = p->lista; l != NULL; l = l->prox){
            if(l->vertice == v){
                return p;
            }
        }
    }
    return NULL;
}

Conjunto *REMOVER_SET(Conjunto *v, Conjunto *W){
    Conjunto *p, *ant;
    p = W;
    ant = W;

    while(p != v){
        ant = p;
        p = p->prox;
    }
    if(p == W){
        W = W->prox;
        return W;
    }
    ant->prox = p->prox;
    return W;

}

Conjunto *UNION(Conjunto *v, Conjunto *u, Conjunto *W){
    Conjunto *menor = inicializaC();
    Conjunto *maior = inicializaC();

    if(v->tamanho < u->tamanho){
        menor = v;
        maior = u;
    }
    else{
        menor = u;
        maior = v;
    }

    Lista *q = maior->lista;
    while(q != NULL){
        menor->lista = insere_inicioLista(menor->lista, q->vertice);
        q = q->prox;
    }
    menor->tamanho += maior->tamanho;
    W = REMOVER_SET(maior, W);
    return W;
}

MST *MST_KRUSKAL(Grafo *G){
    MST *A = inicializaM();
    Conjunto *W = inicializaC();
    Vertice *v;
    
    for(v = G->vertices; v != NULL; v = v->prox){
        W = MAKE_SET(v, W);   
    }
    Aresta *a = inicializaA();
    Vertice *u = inicializaV();

    for(a = G->arestas; a != NULL; a = a->prox){
        v = a->v;
        u = a->u;

        Conjunto *vW, *uW;
        vW = inicializaC();
        uW = inicializaC();
        vW = FIND_SET(v, W);
        uW = FIND_SET(u, W);

        if(vW != uW){
            A = insere_MST(A, a);
            W = UNION(vW, uW, W);
        }
    }
    return A;
}

