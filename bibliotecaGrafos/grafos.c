//Arthur Teixeira Jardim
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"
#include "pilhas.h"
#include "filas.h"
#include "heap.h"
#include "conj.h"

Grafo *parser(Grafo *g, int *tamA){
	FILE *arquivo;
	int vertices, n=0, i=0, a, b, c;
	char texto[100], carac, arq[100];
	printf("\nNome do arquivo: ");
	scanf("%s",arq);
	if((arquivo = fopen(arq,"r")) == NULL){
		printf("Erro ao abrir arquivo.\n");
		exit(1);
	}else{
		fscanf(arquivo,"%d",&vertices);
		g = inicializa(vertices);
		while((carac = fgetc(arquivo)) != EOF){
			if(carac != '\n'){
				texto[n] = carac;
				n++;
			}else{
				texto[n] = '\0';
				if(n > 0){
					a = atoi(strtok(texto,";"));
					b = atoi(strtok(NULL,";"));
					c = atoi(strtok(NULL,"\n"));
				}
				n = 0;
				if(i != 0){
					g = insercao(g, a, b, c);
					*tamA = *tamA + 1;;
				}
				i++;
			}
		}
	}
	fclose(arquivo);
	return g;
}

Grafo *inicializa(int vertices){
	int i;
	//Criação do Grafo;
	Grafo *novoG = (Grafo*)malloc(sizeof(Grafo));
	novoG->tam = vertices;
	novoG->lista = NULL;
	//Criação dos vértices;
	for(i=1; i<vertices+1; i++){
		Nodo *novoN = criaVertice(i);
		if(novoG->lista == NULL){
			novoG->lista = novoN;
		}else{
			//Inserção no final;
			Nodo *temp = novoG->lista;
			while(temp->prox != NULL){
				temp = temp->prox;
			} 
			temp->prox = novoN;
		}
	}
	return novoG;
}

Nodo *criaVertice(int chave){
	Nodo *novoV = (Nodo*)malloc(sizeof(Nodo));
	novoV->chave = chave;
	novoV->prox = NULL;
	return novoV;
}

Grafo *insercao(Grafo *g, int a, int b, int c){
	Nodo *auxN;
	//Busca vértice;
	auxN = busca(g, a);
	//Cria nova aresta;
	Aresta *novoA=(Aresta*)malloc(sizeof(Aresta));
	novoA->chave_partida = a; //Insere aresta de partida;
	novoA->chave_adj = b; //Inere aresta de chegada;
	novoA->peso = c; //Insere peso;
	novoA->prox = NULL;
	if(auxN->adj == NULL){
		//Inserção se for a primeira aresta;
		auxN->adj = novoA;
	}else{
		//Inserção no inicio;
		novoA->prox = auxN->adj;
		auxN->adj = novoA;
	}
	return g;
}

void impressao(Grafo *g){
	Nodo* auxN = g->lista;
	printf("\n");
	while(auxN != NULL){
		Aresta *auxA = auxN->adj;
		while(auxA != NULL){
			printf("%d --%d--> %d\n",auxN->chave, auxA->peso, auxA->chave_adj);
			auxA = auxA->prox;
		}
		auxN = auxN->prox;
	}
}

void liberar(Grafo *g){
	Grafo *p = g;
	Nodo *n = g->lista;
	Aresta *a = g->lista->adj;
	while(a != NULL){
		Aresta *q = a->prox;
		free(a);
		a = q;
	}
	while(n != NULL){
		Nodo *t = n->prox;
		free(n);
		n = t;
	}
	free(p);
}

void buscaDFS(Grafo *g){
	int val, n, v, k, visit[g->tam], i, y;
	Pilha *p = pilha_cria(); //Cria pilha;
	Nodo *bus, *auxN;
	Aresta *auxA;
	printf("Busca apartir de nodo:\n");
	scanf("%d",&val);
	for(i=0; i<g->tam; i++){
		visit[i] = 0;
	}
	bus = busca(g, val); //Busca vértice de inicio;
	if(bus == NULL){
		printf("\nVértice não existente no grafo.\n");
		return;
	}
	y=1;
	visit[0] = val; //Coloca o vértice de inicio na primeira posição do vet solução;
	if(bus != NULL){
		//Coloca todas arestas desse vértice na pilha;
		auxA = bus->adj;
		while(auxA != NULL){
			push(p, auxA->chave_adj, g->tam);
			auxA = auxA->prox;
		}
	}
	while(p->qtde > 0){
		k = 0;
		v = pop(p); //Retira da pilha;
		if(y > g->tam) //Condição para ver se o vetor já está completo;
			break;
		for(i=0; i<g->tam; i++){
			//Verifica se esse vértice já não está na solução;
			if(visit[i] == v)
				k = 1;
		}
		if(k != 1)
			visit[y] = v; //Adiciona vértice ao vetor solução;
		y++;
		auxN = busca(g, v); //Busca esse vértice que saiu da pilha;
		if(auxN != NULL){
			//Adiciona todas arestas de v na pilha;
			auxA = auxN->adj;
			while(auxA != NULL){
				n = 0;
				for(i=0; i<g->tam; i++){
					//Só coloca na pilha os vértices que ainda não estão na solução;
					if(auxA->chave_adj == visit[i]){
						n = 1;
					}
				}
				if(n != 1){
					push(p, auxA->chave_adj, g->tam);
				}
				auxA = auxA->prox;
			}
		}
		 
	}
	printf("\nVértices percorridos:\n");
	for(i=0; i<g->tam; i++){
		printf("%d ",visit[i]);
	}
	
}

Nodo *busca(Grafo *auxG, int val){
	Nodo *auxN, *bus;
	int verifica = 0;
	for(auxN = auxG->lista; auxN != NULL; auxN = auxN->prox){
		if(auxN->chave == val){
			//Busca vértice desejado no grafo.
			bus = auxN;
			verifica = 1;
		}
	}
	if(verifica == 1)
		return bus;
	else
		//Se o vértice não for encontrado retorna NULL;
		return NULL;
}

void buscaBFS(Grafo *g){
	int val, v, visit[g->tam], i, y;
	Fila *f = cria(); //Cria fila;
	Nodo *bus, *auxN;
	Aresta *auxA;
	printf("Busca apartir de nodo:\n");
	scanf("%d",&val);
	for(i=0; i<g->tam; i++){
		visit[i] = 0;
	}
	bus = busca(g, val); //Coloca o vértice de inicio na primeira posição do vet solução;
	if(bus == NULL){
		printf("\nVértice não existente no grafo.\n");
		return;
	}
	y=1;
	visit[0] = val; //Coloca o vértice de inicio na primeira posição do vet solução;
	if(bus != NULL){
		//Coloca todas arestas desse vértice na fila;
		auxA = bus->adj;
		while(auxA != NULL){
			fila_insere(f, auxA->chave_adj, g->tam);
			auxA = auxA->prox;
		}
	}
	int k;
	while(f->n > 0){
		k = 0;
		v = fila_retira(f); //Retira da fila;
		if(y > g->tam) //Condição para ver se o vetor já está completo;
			break;
		for(i=0; i<g->tam; i++){ //Verifica se esse vértice já não está na solução;
			if(visit[i] == v)
				k = 1;
		}
		if(k != 1){
			visit[y] = v; //Adiciona vértice na solução;
			y++;
		}
		auxN = busca(g, v); //Busca o vértice de valor v;
		if(auxN != NULL){
			//Adiciona todas arestas de v na fila;
			auxA = auxN->adj;
			while(auxA != NULL){
				if(auxA->chave_adj != val){				
					fila_insere(f, auxA->chave_adj, g->tam);
				}
				auxA = auxA->prox;
			}
		}
		 
	}
	printf("\nVértices percorridos:\n");
	for(i=0; i<g->tam; i++){
		printf("%d ",visit[i]);
	}
	
}

void kruskal(Grafo *g, int tamA){
	int ac, ap, p, x=0, y=0, solucaoP[tamA], solucaoAC[tamA], solucaoAP[tamA], i, conj[g->tam+1];
	Nodo *auxN;
	Aresta *auxA;
	for(i=0; i<tamA; i++){
		solucaoP[i] = 0;
		solucaoAC[i] = 0;
		solucaoAP[i] = 0;
	}
	Heap *h = (Heap*)malloc(sizeof(Heap));
	h->tam = 0;
	h->arestaChegada = (int*)malloc(tamA*sizeof(int));
	h->peso = (int*)malloc(tamA*sizeof(int));
	h->arestaPartida = (int*)malloc(tamA*sizeof(int));
	makeSet(g->tam, conj); //Criação conjuntos disjuntos
	for(auxN = g->lista; auxN != NULL; auxN = auxN->prox){
		//Coloca todas as arestas do grafo na heap;
		auxA = auxN->adj;
		while(auxA != NULL){
			buildheap(h, auxA->chave_adj, auxA->peso, auxA->chave_partida);
			auxA = auxA->prox;
		}
	}
	while(h->tam > 0){
		if(conj[h->arestaPartida[0]] != conj[h->arestaChegada[0]]){ //Vê se são de conjuntos diferentes;
			ac = h->arestaChegada[0]; //Guarda vert de chegada em ac;
			ap = h->arestaPartida[0]; //Guarda vert de partida em ap;
			p = h->peso[0]; //Guarda peso em p;
			delete(h); //Retira a aresta que foi guardada nas variaveis acima da heap;
			//Coloca a aresta na solução
			solucaoP[x] = p;
			solucaoAC[x] = ac;
			solucaoAP[x] = ap;
			x++;
			uniao(ac, ap, conj, g->tam); //Atualiza conjuntos disjuntos
		}else{
			delete(h); //Retira a aresta da heap que não será inserida na solução;
		}
		y++;
	}
	printf("\nArestas percorridas:\n");
	for(i=0; i<x; i++){
		printf("P(%d)<%d,%d> ",solucaoP[i], solucaoAP[i], solucaoAC[i]);
	}
	free(h->peso);
	free(h->arestaChegada);
	free(h->arestaPartida);
	free(h);
}

void prim(Grafo *g, int tamA){
	int conj[g->tam+1], ap, ac, p, i, x=0, solucaoP[tamA], solucaoAC[tamA], solucaoAP[tamA], estaNaSolucao = 0, val;
	Nodo *auxN;
	Aresta *auxA;
	Heap *h = (Heap*)malloc(sizeof(Heap));
	h->tam = 0;
	h->peso = (int*)malloc(tamA*sizeof(int));
	h->arestaChegada = (int*)malloc(tamA*sizeof(int));
	h->arestaPartida = (int*)malloc(tamA*sizeof(int));
	for(i=0; i<tamA; i++){
		//Inicialização dos vetores da solução 
		solucaoP[i] = 0;
		solucaoAC[i] = 0;
		solucaoAP[i] = 0;
	}
	printf("A partir de qual nodo:\n");
	scanf("%d",&val);
	auxN = busca(g, val); //Busca no grafo do vértice de valor informado;
	if(auxN == NULL){
		printf("\nVértice não existente no grafo.\n");
		return;
	}
	makeSet(g->tam, conj); //Criação conjuntos disjuntos.
	auxA = auxN->adj;
	if(auxA == NULL){
		printf("\nVertice sem arestas de adjacencias.\n");
		return;
	}
	while(auxA != NULL){
		//Coloca todas arestas de vértice buscado na heap;
		buildheap(h, auxA->chave_adj, auxA->peso, auxA->chave_partida);
		auxA = auxA->prox;
	}
	while(h->tam > 0){
		if(conj[h->arestaPartida[0]] != conj[h->arestaChegada[0]]){ //Vê se são de conjuntos diferentes;
			estaNaSolucao = 0;
			//Guarda a aresta de menor peso da heap nas variaveis: ac, ap e p;
			ac = h->arestaChegada[0];
			ap = h->arestaPartida[0];
			p = h->peso[0];
			delete(h); //Deleta a aresta da heap;
			for(i=0; i<x; i++){
				//Verifica se a aresta já não está na solução;
				if(solucaoP[i] == p && solucaoAC[i] == ac && solucaoAP[i] == ap){
					estaNaSolucao = 1;
				}
			}
			if(estaNaSolucao == 0){
				//Se não está na solução é inserida nela;
				solucaoAC[x] = ac;
				solucaoP[x] = p;
				solucaoAP[x] = ap;
				x++;
				auxN = busca(g, ac); //Busca o vértice de chegada da aresta acima;
				auxA = auxN->adj;
				while(auxA != NULL){
					//Coloca todas arestas do vértice na heap;
					buildheap(h, auxA->chave_adj, auxA->peso, auxA->chave_partida);
					auxA = auxA->prox;
				}
			}
			uniao(ac, ap, conj, g->tam); //Faz união dos conjuntos disjuntos;
		}
		else
			delete(h); //Se são do mesmo conjunto, deleta a aresta;
	}
	printf("\nArestas percorridas:\n");
	for(i=0; i<x; i++){
		printf("P(%d)<%d,%d> ",solucaoP[i], solucaoAP[i], solucaoAC[i]);
	}
	free(h->peso);
	free(h->arestaChegada);
	free(h->arestaPartida);
	free(h);
}

void dijkstra(Grafo *g, int tamA){
	int solucao[g->tam], d[g->tam+1], pi[g->tam+1], i, v, p, u, x, k, val;
	Nodo *auxN;
	Aresta *auxA;
	for(i=0; i<g->tam; i++){
		//Inicialização vetor solução (vértices percorridos).
		solucao[i] = 0;
	}
	for(i=1; i<g->tam+1; i++){
		//Inicializando o vetor D com valor alto 
		d[i] = 9999999;
		pi[i] = 0;
	}
	//Começo do algoritmo
	printf("Começa: \n");
	scanf("%d",&val);
	//Alocação da heap
	Heap *h = (Heap*)malloc(sizeof(Heap));
	h->tam = 0;
	h->peso = (int*)malloc(g->tam*sizeof(int));
	h->arestaChegada = (int*)malloc(g->tam*sizeof(int));
	h->arestaPartida = (int*)malloc(g->tam*sizeof(int));
	d[val] = 0;
	//Busca do primeiro valor
	auxN = busca(g, val);
	if(auxN == NULL){
		printf("\nVértice não existente no grafo.\n");
		return;
	}
	auxA = auxN->adj;
	while(auxA != NULL){
		//Colocar todas arestas do vértice inicial na heap
		buildheap(h, auxA->chave_adj, auxA->peso, auxA->chave_partida);
		auxA = auxA->prox;
	}
	//Colocar primeiro valor buscado no vetor de vértices percorridos
	solucao[0] = auxN->chave;
	x = 1;
	while(h->tam > 0){
		//Guarda a aresta de menor peso da heap nas variaveis: u, v e p;
		u = h->arestaPartida[0];
		v = h->arestaChegada[0];
		p = h->peso[0];
		//Exclusão da heap
		delete(h);
		k = 0;
		for(i=0; i<g->tam; i++){ //Verifica se o vértice de chegada já está na solução.
			if(solucao[i] == v){
				k = 1;
			}
		}
		if(k != 1){
			//Adiciona o vértice na solução.
			solucao[x] = v;
			x++;
		}
		if(d[v] > d[u] + p){ //Verifica se o peso para o vértice antigo é maior que o peso atual.
			pi[v] = u;
			d[v] = d[u]+p; //Caso o atual seja menor é atualizado o peso do caminho para o vértice
			auxN = busca(g, v); //Busca do vértice de chegada. 
			auxA = auxN->adj;
			while(auxA != NULL){
				//Adiciona todas arestas do vértice de chegada na heap.
				buildheap(h, auxA->chave_adj, auxA->peso, auxA->chave_partida);
				auxA = auxA->prox;
			}
		}
	}
	printf("\nVértices percorridos:\n");
	for(i=0; i<x; i++){
		printf("%d ",solucao[i]);
	}
	printf("\n\nPeso para chegar a cada vertice:\n");
	i = 1;
	while(i<x+1){
		if(d[i] != 9999999){
			printf("Vertice: %d | Passou pelo vertice: %d | Peso: %d\n", i, pi[i], d[i]);
		}else{
			x++;
		}
		i++;
	}
	free(h->peso);
	free(h->arestaChegada);
	free(h->arestaPartida);
	free(h);
}

void finalmenu(){
	printf("\n\nEnter para continuar...\n");
	getchar();
	getchar();
}
