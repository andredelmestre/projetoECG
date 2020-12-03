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
	if(tamanho <= 1 ){
		return *( vet + 0 ) / ctrl ;
	}else{
		return *( vet + tamanho - 1) / ctrl + mediaVetRecursiva(vet, tamanho-1, ctrl);
	}
}

int procuraZonaR(float * vetECG, int tamanho, int * inicio_pico_R, int * fim_pico_R, float valorInteresse){
	int i, conta_picos_R = 0, flag = 0;

	for(i=0; i<tamanho; i++){
		if(vetECG[i] > valorInteresse && flag == 0){
			*(inicio_pico_R + conta_picos_R) = i;
			flag = 1;
		}else if(vetECG[i] < valorInteresse && flag == 1){
			*(fim_pico_R + conta_picos_R) = i;
			flag = 0;
			conta_picos_R++;
		}
	}
	return conta_picos_R;
}

float calcBPM(int dist_pontos, float freq){
	float tempo1batida = dist_pontos / freq;
	float BPM = 60 / tempo1batida;
	return BPM;
}
