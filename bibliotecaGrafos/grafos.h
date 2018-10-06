//Arthur Teixeira Jardim
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
	int chave; 
	struct nodo *prox;
	struct aresta *adj;
}; typedef struct nodo Nodo;

struct grafo{
	Nodo *lista;
	int tam;
}; typedef struct grafo Grafo;

struct aresta{
	int chave_partida;
	int chave_adj;
	struct aresta *prox;
	int peso; 
}; typedef struct aresta Aresta;

Grafo *parser(Grafo *g, int *tamA);
Grafo *inicializa(int vertices);
Nodo *criaVertice(int chave);
Nodo *buscaVertice(Grafo *g, int busca);
void impressao(Grafo *g);
Grafo *insercao(Grafo *g, int a, int b, int c);
void liberar(Grafo *g);
void buscaDFS(Grafo *g);
Nodo *busca(Grafo *g, int val);
int falta(int *visit, int v, Grafo *g);
void buscaBFS(Grafo *g);
void kruskal(Grafo *g, int tamA);
void prim(Grafo *g, int tamA);
void dijkstra(Grafo *g, int tamA);
void finalmenu();
