#include <stdio.h>
#include <stdlib.h>
#include "andre.h"


float maior(float a, float b){
	if(a>b)
		return a;
	else
		return b;
}

float maiorVet(float *vet, int tamanho){
	int i;
	float maiorNum = *(vet+0);		// maiorNum = vet[0]
	for(i=1; i<tamanho; i++)
		maiorNum = maior(maiorNum , *(vet+i) ); 	// maiorNum = maior(maiorNum , vet[i] );
	return maiorNum;
}

int maiorValorVetIndex(float *vet, int tamanho){
	int i, indMaior=0;
	float maiorNum = *(vet+0);		// maiorNum = vet[0]
	for(i=1; i<tamanho; i++){
		if(*(vet+i) > maiorNum){
			indMaior = i;
			maiorNum = *(vet+i);
		}
	}
	return indMaior;
}


float mediaVet(float *vet, int tamanho){
	int i;
	float soma = *(vet+0);		// soma = vet[0]
	for(i=1; i<tamanho; i++)
		soma += *(vet+i); 	// soma = soma + vet[i];
	return soma / tamanho;
}

// [0]		4
// [1]		6
// [2]		8

//4/3 + 6/3 + 8/3 = (4+6+8)/3 = 6

float mediaVetRecursiva(float *vet, int tamanho, int ctrl){
	if( ctrl >= tamanho){
		return 0 ;
	}else{
		return *vet / tamanho + mediaVetRecursiva(vet+1, tamanho, ctrl+1);
	}
}





//retornar o num de picos R do vetor vetECG
int identificaPicosR(float * vetECG, int tamanhoECG, int * inicioZonaInteresse, int * fimZonaInteresse, float pico_R_referencia){
	int i, contaPicos=0, flagInteresse=0;
	for(i=0; i<600; i++){
		if( * (vetECG + i) > pico_R_referencia && flagInteresse == 0){
			inicioZonaInteresse[contaPicos] = i;
			flagInteresse = 1;
			// printf("inicioZonaInteresse = %i\n", inicioZonaInteresse);
		}else if( vetECG[i] < pico_R_referencia  && flagInteresse == 1) {
			fimZonaInteresse[contaPicos] = i;
			flagInteresse = 0;
			// printf("fimZonaInteresse = %i\n", fimZonaInteresse);
			contaPicos++;
		}
	}
	return contaPicos;
}

float calculaBPM(float freq, int dist_pontos){
	float umaBatida = dist_pontos / freq;
	float BPM = 60/umaBatida;
	return BPM;
}