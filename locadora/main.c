#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locadora.h"

int main(){
	int tam = tamanho();
	Filme *f[tam];
	int op, op2, op3, op4, ano, qtdOriginal[tam], codigo;
	char genero[10], titulo[100];
	inicializaStruct(f ,tam);
	preencheStruct(f, qtdOriginal);	
	while(1){
		system("clear");
		printf("\n    Locadora do Alcemar\n\n");
		printf("1. Locar um filme.\n");
		printf("2. Entregar um filme.\n");
		printf("3. Buscar filmes.\n");
		printf("4. Relatórios.\n");
		printf("5. Impressão.\n");
		printf("0. Sair.\n");
		printf("\nEscolha uma opção acima:\n");
		scanf("%d",&op);
		switch(op){
			case 0:
				liberaStruct(f, tam);
				return 0;
			case 1:
				system("clear");
				printf("\n       Locação de filmes\n\n");
				printf("\nInforme o código do filme para locação:\n");
				scanf("%d",&codigo);
				locacaoCodigo(f, codigo, qtdOriginal, tam);
				printf("\nPressione enter para continuar...");
    			getchar();
    			getchar();
    			break;
    		case 2:
				system("clear");
				printf("\n       Entrega de filmes\n\n");
    			printf("\nInforme o código do filme para entrega:\n");
				scanf("%d",&codigo);
				entregaCodigo(f, codigo, qtdOriginal, tam);
				printf("\nPressione enter para continuar...");
    			getchar();
    			getchar();
    			break;
    		case 3:
				system("clear");
				printf("\n       Busca de filmes\n\n");
				printf("-> 1 - Buscar por codigo.\n");
				printf("-> 2 - Buscar por nome.\n");
				printf("-> 3 - Buscar por ano.\n");
				printf("-> 4 - Buscar por genero.\n");
				printf("-> Escolha uma opção de busca:\n");
				scanf("%d",&op2);
    			menuBusca(f, op2, tam);
				printf("\nPressione enter para continuar...");
    			getchar();
    			getchar();
    			break;
    		case 4:
				printf("-> 1 - Relatório por ano.\n");
				printf("-> 2 - Relatório por genêro.\n");
				printf("-> 3 - Acervo completo.\n");
				printf("-> Escolha uma opção acima:\n");
				scanf("%d",&op3);
				if(op3==1){
					printf("Informe ano: ");
					scanf("%d",&ano);
					relatorioAno(f, ano, tam);
				}
				if(op3==2){
					printf("Informe gênero: ");
					scanf("%s",genero);
					relatorioGenero(f, genero, tam);
				}
				if(op3==3){
					acervoCompleto(f, tam);
				}
				printf("\nPressione enter para continuar...");
    			getchar();
    			getchar();				
				break;
			case 5:
				printf(" -> 1. Impressão de filme específico.\n");
				printf(" -> 2. Impressão de todos filmes.\n");
				printf(" Escolha opção acima: ");
				scanf("%d",&op4);
				if(op4 == 1){
					printf("Digite título: ");
					scanf(" %100[^\n]",titulo);
					buscaTitulo(f, titulo, tam);
				}
				if(op4 == 2){
					buscaTodos(f, tam);
				}
				if(op4!=1 && op4!=2){
					printf("Operação inválida.\n");
				}
				printf("\nPressione enter para continuar...");
    			getchar();
    			getchar();				
				break;
			default:
				printf("Opção invalida!\n");
				break;
		}	
	} 
	return 0;
}
