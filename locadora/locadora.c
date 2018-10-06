#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "locadora.h"

//Função para ler a primeira linha que contém o numero de filmes do acervo.
int tamanho(){ 
	FILE *arquivo;
	char texto[32];
	int tam;
	arquivo = fopen("entrada.txt","r");
	if(arquivo == NULL){
		printf("Erro ao abrir arquivo.");
		exit(1);
	}else{
		fscanf(arquivo,"%s",texto); //Primeira linha armazenada na variavel texto.
		tam = atoi(texto); //Transformada em inteiro.
	}
	return tam;
}	

//Inicialização da struct 
void inicializaStruct(Filme **f, int tam){
	int i;
	for(i=0; i<tam; i++){
		f[i] = NULL;
	}
}

//Preenchimento da struct
void preencheStruct(Filme **f, int *qtdOriginal){
	int i=0;
	char texto[100], ano[5], qtde[3];
	FILE *arquivo;
	arquivo = fopen("entrada.txt","r"); //Abrindo arquivo do banco de dados.
	if(arquivo == NULL){
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}else{
		while((fgets(texto, 99, arquivo)) != NULL){
 			if(i!=0){ //A partir da segunda linha do banco de dados.
 				f[i-1] = (Filme*)malloc(sizeof(Filme)); //Alocação de memoria na struct.
 			 	f[i-1]->codigo = i; //Geração do código.
				strcpy(f[i-1]->titulo, strtok(texto, ";")); //Desmembrando as linhas e colocando as informações nos campos da struct.
				strcpy(ano, strtok(NULL, ";")); 
				strcpy(qtde, strtok(NULL, ";"));
				strcpy(f[i-1]->genero, strtok(NULL, "\n"));
				f[i-1]->ano = atoi(ano); //Transfomando a variavel ano "string" para "inteiro".
				f[i-1]->quantidade = atoi(qtde); //Transfomando a variavel qtde "string" para "inteiro".
				qtdOriginal[i-1] = f[i-1]->quantidade; //Colocando a quantidade de filmes retirada do banco de dados para as posições do vetor.
			}
			i++;
		}
	}
	fclose(arquivo);
}

//Função de locação de filmes.
void locacaoCodigo(Filme **f, int codigo, int *qtdOriginal, int tam){
	int i;
	for(i=0; i<tam; i++){
		if(codigo == f[i]->codigo){ //Comparação para ver se os códigos são iguais.
			if(f[i]->quantidade > 0){ //Caso não haja filmes com mesmo titulo caí nessa condição.
				f[i]->quantidade = f[i]->quantidade - 1; //Decrementa a quantidade.
				printf("\nFilme locado com sucesso!\n");
				printf("\nInformacoes do filme locado:\n");
				printf("Titulo: %s\n", f[i]->titulo);
				printf("Genero: %s\n", f[i]->genero);
				printf("Ano: %d\n", f[i]->ano);
				return;
			}else{
				//Cai nessa condição se todos filmes ja foram locados.
				printf("\nFilme Indisponivel no momento.\nTodas as copias foram locadas.\n\n");
				return;
			}
		}
	}
	//Cai nessa condição se o filme não é encontrado no acervo.
	printf("\nFilme nao encontrado.\n");
}

//Função de entrega dos filmes.
void entregaCodigo(Filme **f, int codigo, int *qtdOriginal, int tam){
	int i;
	for(i=0; i<tam; i++){
		if(codigo == f[i]->codigo){
			if(f[i]->quantidade < qtdOriginal[i]){ //Verifica se já estão todos filmes entregues.
				f[i]->quantidade = f[i]->quantidade + 1; //Incrementa a quantidade.
				printf("\nFilme entregue com sucesso.\n");
				return;
			}else{
				//Cai nessa condição se todos filmes ja estão no acervo.
				printf("\nNao foi possivel realizar a entrega.\nTodas as copias estao no acervo.\n");
				return;	
			}
		}
	}
	//Cai nessa condição se não encontramos o filme no acervo.
	printf("\nNao possuimos esse filme.\nVerifique se digitou o código correto.\n");
}

void menuBusca(Filme **f, int op, int tam){ //Menu para escolhas de busca.
	int code, ano;
	char name[100], genero[10];
	switch(op){
		case 1: //Busca por código.
			printf("Digite codigo para busca: ");
			scanf("%d",&code);
			buscaCodigo(f, code, tam);
			break;
		case 2: //Busca por nome.
			printf("Digite nome para busca: ");
			scanf(" %100[^\n]",name);
			buscaTitulo(f, name, tam);
			break;
		case 3: //Busca por ano.
			printf("Digite ano para busca: ");
			scanf("%d",&ano);
			buscaAno(f, ano, tam);
			break;
		case 4: //Busca por genero
			printf("Digite genero para busca: ");
			scanf(" %10[^\n]",genero);
			buscaGenero(f, genero, tam);
			break;
		default:
			printf("Opção invalida!\n");
			break;
	}
}

//Busca filme por codigo.
void buscaCodigo(Filme **f, int code, int tam){
	system("clear");
	printf("\n       Busca de filmes por codigo.\n");
	int i;
	for(i=0; i<tam; i++){
		if(f[i]->codigo == code){
			printf("\nCodigo: %d\n", f[i]->codigo);
			printf("Titulo: %s\n", f[i]->titulo);
			printf("Ano: %d\n", f[i]->ano);
			printf("Quantidade: %d\n", f[i]->quantidade);
			printf("Genero: %s\n", f[i]->genero);
			return;
		}
	}
	printf("Código não encontrado!\n");
}

//Busca filme por titulo.
void buscaTitulo(Filme **f, char *name, int tam){ 
	system("clear");
	printf("\n       Busca de filmes por título.\n");
	int i, x;
	for(i=0; i<tam; i++){
		if(strcasecmp(f[i]->titulo, name)==0){
			printf("\nCodigo: %d\n", f[i]->codigo);
			printf("Titulo: %s\n", f[i]->titulo);
			printf("Ano: %d\n", f[i]->ano);
			printf("Quantidade: %d\n", f[i]->quantidade);
			printf("Genero: %s\n", f[i]->genero);
			x = 1;
		}
	}
	if(x!=1) printf("Titulo não encontrado!\n");
}

//Busca filme por ano.
void buscaAno(Filme **f, int ano, int tam){ 
	int x;
	system("clear");
	printf("\n       Busca de filmes por ano.\n");
	int i;
	for(i=0; i<tam; i++){
		if(f[i]->ano == ano){
			printf("\nCodigo: %d\n", f[i]->codigo);
			printf("Titulo: %s\n", f[i]->titulo);
			printf("Ano: %d\n", f[i]->ano);
			printf("Quantidade: %d\n", f[i]->quantidade);
			printf("Genero: %s\n", f[i]->genero);
			x = 1;
		}
	}
	if(x!=1) printf("Não foram encontrados filmes com esse ano de lançamento!\n");
}

//Busca filme por genero.
void buscaGenero(Filme **f, char *genero, int tam){ 
	int x;
	system("clear");
	printf("\n       Busca de filmes por gênero.\n");
	int i;
	for(i=0; i<tam; i++){
		if(strcasecmp(f[i]->genero, genero)==0){
			printf("\nCodigo: %d\n", f[i]->codigo);
			printf("Titulo: %s\n", f[i]->titulo);
			printf("Ano: %d\n", f[i]->ano);
			printf("Quantidade: %d\n", f[i]->quantidade);
			printf("Genero: %s\n", f[i]->genero);
			x = 1;
		}
	}
	if(x!=1) printf("Gênero não encontrado!\n");
}

//Busca de todos filmes
void buscaTodos(Filme **f, int tam){
	system("clear");
	printf("\n       Impressão todos filmes.\n");
	int i;
	for(i=0; i<tam; i++){
		printf("\nCodigo: %d\n", f[i]->codigo);
		printf("Titulo: %s\n", f[i]->titulo);
		printf("Ano: %d\n", f[i]->ano);
		printf("Quantidade: %d\n", f[i]->quantidade);
		printf("Genero: %s\n", f[i]->genero);
	}
}

//Relatório por ano.
void relatorioAno(Filme **f, int ano, int tam){
	system("clear");
	printf("\n       Relatório por ano.\n");
	int i, x;
	FILE *arquivo;
	char op, texto[100];
	arquivo = fopen("relatorio_ano.txt","w");
	if(arquivo == NULL){
		printf("Erro ao abrir arquivo.\n");
		exit(1);
	}else{
		for(i=0; i<tam; i++){
			if(f[i]->ano == ano){ //Se os anos forem iguais é armazenado os dados no arquivo.
				fprintf(arquivo,"%s;%d;%d;%s\n", f[i]->titulo, f[i]->ano, f[i]->quantidade, f[i]->genero);
				x=1;
			}
		}
	}
	if(x==1) printf("Relatorio gerado com sucesso!\n"); 
	if(x!=1){
		//Cai nessa condição se não foram encontrados filmes com esse ano no acervo.
		printf("Ano não encontrado.\n");
		return;
	}
	fclose(arquivo);
	printf("\nDeseja ler relatorio? [S/N]\n"); //Opção para caso queira ler o relatorio que foi gerado.
	scanf("%s",&op);
	arquivo = fopen("relatorio_ano.txt","r"); //Abre o arquivo.
	if(op=='s' || op=='S'){
		if(arquivo == NULL){ 
			printf("Erro ao abrir arquivo.\n");
			exit(1);
		}else{
			printf("\n");
			while(fgets(texto,99,arquivo)!=NULL){ //Lê o relatório.
				printf("%s",texto); 
			}
			printf("\n");
		}
	}
	fclose(arquivo);	
}

//Relatório por genêro
void relatorioGenero(Filme **f, char *genero, int tam){
	system("clear");
	printf("\n       Relatório por gênero.\n");
	int i, x;
	FILE *arquivo;
	char op, texto[100];
	arquivo = fopen("relatorio_genero.txt","w");
	if(arquivo == NULL){
		printf("Erro ao abrir arquivo.\n");
		exit(1);
	}else{
		for(i=0; i<tam; i++){
			if((strcasecmp(f[i]->genero, genero))==0){ //Se os genêros forem iguais é armazenado os dados no arquivo.
				fprintf(arquivo,"%s;%d;%d;%s\n", f[i]->titulo, f[i]->ano, f[i]->quantidade, f[i]->genero);
				x=1;
			}
		}
	}
	if(x==1) printf("Relatorio gerado com sucesso!\n");
	if(x!=1){
		//Cai nessa condição se não foram encontrados filmes com esse genêro no acervo.
		printf("Ano não encontrado.\n");
		return;
	}
	fclose(arquivo);
	printf("\nDeseja ler relatorio? [S/N]\n"); //Opção para caso queira ler o relatorio que foi gerado.
	scanf("%s",&op);
	arquivo = fopen("relatorio_genero.txt","r"); //Abre o arquivo.
	if(op=='s' || op=='S'){
		if(arquivo == NULL){
			printf("Erro ao abrir arquivo.\n");
			exit(1);
		}else{
			printf("\n");
			while(fgets(texto,99,arquivo)!=NULL){ //Lê o relatório.
				printf("%s",texto);
			}
			printf("\n");
		}
	}
	fclose(arquivo);		
}

void acervoCompleto(Filme **f, int tam){
	system("clear");
	printf("\n       Acervo completo.\n");
	int i;
	FILE *arquivo;
	char op, texto[100];
	arquivo = fopen("acerto_completo_atual.txt","w");
	if(arquivo == NULL){
		printf("Erro ao abrir arquivo.\n");
		exit(1);
	}else{
		for(i=0; i<tam; i++){ //É colocado todos os filmes no relatório com informações atualizadas.
			fprintf(arquivo,"%s;%d;%d;%s\n", f[i]->titulo, f[i]->ano, f[i]->quantidade, f[i]->genero);
		}
		printf("\nArquivo criado com sucesso.\n");
	}
	fclose(arquivo);
	printf("\nDeseja ler relatorio? [S/N]\n"); //Opção para caso queira ler o relatório que foi gerado.
	scanf("%s",&op);
	arquivo = fopen("acerto_completo_atual.txt","r"); //Abre arquivo.
	if(op=='s' || op=='S'){
		if(arquivo == NULL){
			printf("Erro ao abrir arquivo.\n");
			exit(1);
		}else{
			printf("\n");
			while(fgets(texto,99,arquivo)!=NULL){ //Lê relatório.
				printf("%s",texto);
			}
			printf("\n");
		}
	}
	fclose(arquivo);	
}

//Liberação da struct.
void liberaStruct(Filme **f, int tam){
	int i;
	for(i=0; i<41; i++){
		free(f[i]);
	}
}
