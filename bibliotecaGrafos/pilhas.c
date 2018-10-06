//Arthur Teixeira Jardim
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilhas.h"

Pilha *pilha_cria(){
	int i;
	Pilha *p = (Pilha*)malloc(sizeof(Pilha));
	p->qtde = 0;
	for(i=0; i<N; i++){
		p->vet[i] = 0;
	}
	return p;
}

void push(Pilha *p, int v, int tam){
	if(p->qtde < tam){
		p->vet[p->qtde] = v;
		p->qtde++;	
	}
}

int pop(Pilha *p){
	int v;
	if(p->qtde > 0){
		v = p->vet[p->qtde - 1];
		p->qtde--;
	}
	return v;
}
void teste(Pilha *p, int tam){
	int i;
	for(i=0; i<tam; i++){
		p->vet[i] = 0;
	}
}

void liberarPilha(Pilha *p){
	free(p);
}

int estaPilha(Pilha *p, int v){
	int i, y=1;
	for(i=0; i<N; i++){
		if(p->vet[i] == v){
			y = 0;
		}
	}
	return y;
}
