//Arthur Teixeira Jardim
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"
#include "conj.h"

int main(){
	Grafo *g = NULL;
	int op, tamA=0;
	while(1){
		system("clear");
		printf("\nGRAFOS\n1 - Criar grafos a partir do txt.");
		printf("\n2 - Imprimir o grafo.");
		printf("\n3 - Kruskal.");
		printf("\n4 - DFS.");
		printf("\n5 - BFS.");
		printf("\n6 - Prim.");
		printf("\n7 - Dijkstra.");
		printf("\n0 - Quit.");
		printf("\nEscolha uma opcão acima: ");
		scanf("%d",&op);
		switch(op){
			case 1:
				g = parser(g, &tamA);
				printf("Grafo criado com sucesso.\n");
				finalmenu();
				break;
			case 2:
				if(g == NULL){
					printf("\nNenhum grafo criado.\n");
					finalmenu();
					break;
				}
				impressao(g);
				finalmenu();
				break;
			case 3:
				if(g == NULL){
					printf("\nNenhum grafo criado.\n");
					finalmenu();
					break;
				}
				kruskal(g, tamA);
				finalmenu();
				break;
			case 4:
				if(g == NULL){
					printf("\nNenhum grafo criado.\n");
					finalmenu();
					break;
				}
				buscaDFS(g);
				finalmenu();
				break;
			case 5:
				if(g == NULL){
					printf("\nNenhum grafo criado.\n");
					finalmenu();
					break;
				}
				buscaBFS(g);
				finalmenu();
				break;
			case 6:
				if(g == NULL){
					printf("\nNenhum grafo criado.\n");
					finalmenu();
					break;
				}
				prim(g, tamA);
				finalmenu();
				break;
			case 7:
				if(g == NULL){
					printf("\nNenhum grafo criado.\n");
					finalmenu();
					break;
				}
				dijkstra(g, tamA);
				finalmenu();
				break;
			case 0:
				if(g != NULL){
					liberar(g);
				}
				return 0;
		}
	}
	return 0;
}

