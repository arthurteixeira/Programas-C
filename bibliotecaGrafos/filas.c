#include <stdio.h>
#include <stdlib.h>
#include "filas.h"

Fila *cria(){
	Fila *f = (Fila*)malloc(sizeof(Fila));
	f->n = 0;
	f->ini = 0;
	return f;
}

void fila_insere(Fila *f, int v, int tam){
	int fim, i, z=0;
	if(f->n != K){
		fim = (f->ini + f->n)%tam;
		for(i=0; i<tam; i++){
			if(f->vet[i] == v)
				z = 1;
		}
		if(z != 1){
			f->vet[fim] = v;
			f->n++;
		}
	}else{
		exit(1);
	}
}

int fila_retira(Fila *f){
	int v;
	if(f->n != 0){
		v = f->vet[f->ini];
		f->n--;
		f->ini = (f->ini +1)%K;
		return v;
	}else{
		exit(1);
	}
}

