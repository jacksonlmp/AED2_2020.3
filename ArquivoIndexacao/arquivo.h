#ifndef ARQUIVO_H
#define ARQUIVO_H

typedef struct livro {
	char * titulo;
	char * autor;
	char * isbn;
	int codigo;
} dado;

typedef struct indice {
	int chave;
	int indice;
} tipo_dado;

typedef struct no_avl {
	tipo_dado *dado;
	int fb;
	struct no_avl *esq, *dir;
} no_avl;

typedef no_avl * arvore;

typedef struct tabela {
	FILE *arquivo_dados;
	arvore indices;
} tabela;

int inicializarTabela(tabela *tab);
void adicionarLivro(tabela *tab, dado *livro);
void finalizar (tabela *tab);
void inicializar(arvore *raiz);

int altura(arvore raiz);
int maior(int a, int b);

void pre_order(arvore raiz, tabela *tab);
void pos_order(arvore raiz, tabela *tab);
void in_order(arvore raiz, tabela *tab);
tipo_dado * maior_elemento(arvore raiz);
tipo_dado * menor_elemento(arvore raiz);

arvore carregar_arquivo(char *nome, arvore a);
arvore rotacionar(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);
arvore adicionar (tipo_dado *valor, arvore raiz,int *cresceu);

void buscar(int valor,arvore raiz,tabela *tab);
void imprimir_elemento(arvore raiz, tabela *tab);
void tirar_enter(char *string);
void salvar_arquivo(char *nome, arvore a);
void salvar_auxiliar(arvore raiz, FILE *arq);
dado * ler_dados();

#endif

