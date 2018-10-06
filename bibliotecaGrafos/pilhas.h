//Arthur Teixeira Jardim
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 7

struct pilha{
	int vet[N];
	int qtde;
}; typedef struct pilha Pilha;

Pilha *pilha_cria();
void push(Pilha *p, int v, int tam);
int pop(Pilha *p);
void liberarPilha(Pilha *p);
void teste(Pilha *p, int tam);
int estaPilha(Pilha *p, int v);
