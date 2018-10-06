#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void buildheap(Heap *h, int ac, int ps, int ap){
	h->arestaChegada[h->tam] = ac;
	h->peso[h->tam] = ps;
	h->arestaPartida[h->tam] = ap;
	h->tam = h->tam + 1;
	percolate(h);	
}

void percolate(Heap *h){
	int i, j, Min, aux, aux2, aux3;
	for(i=0; i<h->tam-1; i++){
		Min = i;
		for(j=i+1 ; j<h->tam; j++){
			if (h->peso[j] < h->peso[Min]){
				Min = j;
				aux = h->arestaChegada[Min];
				aux2 = h->peso[Min];
				aux3 = h->arestaPartida[Min];
				h->arestaChegada[Min] = h->arestaChegada[i];
				h->peso[Min] = h->peso[i];
				h->arestaPartida[Min] = h->arestaPartida[i];
				h->arestaChegada[i] = aux;
				h->peso[i] = aux2;
				h->arestaPartida[i] = aux3;
			}
		}
	}
}

void delete(Heap *h){
	h->arestaChegada[0] = h->arestaChegada[h->tam-1];
	h->peso[0] = h->peso[h->tam-1];
	h->arestaPartida[0] = h->arestaPartida[h->tam-1];
	h->tam = h->tam - 1;
	siftdown(h);
}

void dd(Heap *h){
	int k;
	for(k=0; k<h->tam; k++){
			h->peso[k] = h->peso[k+1];
			h->arestaChegada[k] = h->arestaChegada[k+1];
			h->arestaPartida[k] = h->arestaPartida[k+1];
		
	}	
}
void siftdown(Heap *h){
	int i, aux, aux2, aux3;
	for(i=0; i<h->tam; i++){
		aux = 0; aux2 = 0; aux3 = 0;
		if(h->peso[i] > h->peso[i+1]){
			aux = h->arestaChegada[i];
			aux2 = h->peso[i];
			aux3 = h->arestaPartida[i];
			h->arestaChegada[i] = h->arestaChegada[i+1];
			h->peso[i] = h->peso[i+1];
			h->arestaPartida[i] = h->arestaPartida[i+1];
			h->arestaChegada[i+1] = aux;
			h->peso[i+1] = aux2;
			h->arestaPartida[i+1] = aux3;
		}
	}
}

void imprimir(Heap *h){
	int i;
	for(i=0 ;i<h->tam;i++){
		printf("<%d,%d>P(%d) ",h->arestaPartida[i], h->arestaChegada[i], h->peso[i]);
	}
	printf("\n");
}
