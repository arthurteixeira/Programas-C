struct filme{
	int codigo;
	char titulo[100];
	int ano;
	int quantidade;
	char genero[10];
};
typedef struct filme Filme;
void preencheStruct(Filme **f, int *qtdOriginal);
int tamanho();
void inicializaStruct(Filme **f, int tam);
void locacaoCodigo(Filme **f, int codigo, int *qtdOriginal, int tam);
void entregaCodigo(Filme **f, int codigo, int *qtdOriginal, int tam);
void menuBusca(Filme **f, int op, int tam);
void buscaCodigo(Filme **f, int code, int tam);
void buscaTitulo(Filme **f, char *name, int tam);
void buscaAno(Filme **f, int ano, int tam);
void buscaGenero(Filme **f, char *genero, int tam);
void buscaTodos(Filme **f, int tam);
void relatorioAno(Filme **f, int ano, int tam);
void relatorioGenero(Filme **f, char *genero, int tam);
void acervoCompleto(Filme **f, int tam);
void liberaStruct(Filme **f, int tam);