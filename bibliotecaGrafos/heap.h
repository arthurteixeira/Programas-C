#include <stdio.h>
#include <stdlib.h>

struct heap{
	int *arestaChegada;
	int *peso;
	int *arestaPartida;
	int tam;
};

typedef struct heap Heap;

void buildheap(Heap *h, int ac, int ps, int ap);
void percolate(Heap *h);
void delete(Heap *h);
void siftdown(Heap *h);
void imprimir(Heap *h);
void dd(Heap *h);
