#include <stdio.h>
#include <stdlib.h>
#include "conj.h"


void makeSet(int tam, int *conj){
	int i;
	for(i=1; i<tam+1; i++){
		conj[i] = i;
	}
}

int *uniao(int i, int j, int *conj, int tam){
	int x, menorv, maiorv;
	if(conj[i] < conj[j]){
		menorv = i;
		maiorv = j;
	}else{
		menorv = j;
		maiorv = i;
	}
	for(x=1; x<tam+1; x++){
		if(conj[x] == conj[maiorv] && x != maiorv){
			conj[x] = findSet(menorv, conj);
		}
	}
	conj[maiorv] = findSet(menorv, conj);
	return conj;
}

int findSet(int i, int *conj){
	if(conj[i] == i){
		return i;
	}else{
		conj[i] = findSet(conj[i], conj);
		return (conj[i]);
	}
}
