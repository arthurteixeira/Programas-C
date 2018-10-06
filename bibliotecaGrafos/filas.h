#include <stdio.h>
#define K 10

struct fila{
	int n;
	int ini;
	int vet[K];
};

typedef struct fila Fila;
Fila *cria();
void fila_insere(Fila *f, int v, int tam);
int fila_retira(Fila *f);
