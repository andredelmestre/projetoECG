#include <stdio.h>
#include <stdlib.h>

#include "lib.h"


int main (){
	// char nomeArqAmostras[] = "100";
	char nomeArqAmostras[] = "ecg";
	char arqOriginal[30], arqFiltrado[40];
	
	geraNomes(nomeArqAmostras, arqOriginal, arqFiltrado);

	printf("arqOriginal = %s \t arqFiltrado = %s\n", arqOriginal, arqFiltrado);
	pause();

// 	float samples[600] = {
// 		40.198505,
// 		38.948036,
// ...
// 		37.908623, 
// 		38.947327
// 	};

	int nSamples = contaLinhas(arqFiltrado);

	float *samples = leAmostras(arqFiltrado, nSamples);

	printf("verificando se o array dinamico 'samples' esta disponivel no main\n");
	printArrayFloat(samples+200, 10);

	pause();

	float maior_pico_R = maiorVet(samples, nSamples);

	printf("maior_pico_R = %f\n", maior_pico_R);

	float media = mediaVetRecursiva(samples, 600, 0); 
	printf("media = %f\n", media);

	float pico_R_referencia = (maior_pico_R+media)/2;

	printf("pico_R_referencia = %f\n", pico_R_referencia);

	pause();

	int inicioZonaInteresse[15], fimZonaInteresse[15], nPicosR=0;
	nPicosR = contaPicosR(samples, nSamples, pico_R_referencia);

	printf("nPicosR = %i\n", nPicosR);

	pause();


	int * picos_R = geraPicosR(samples, nSamples, pico_R_referencia, nPicosR);
	// int picos_R[15]; 

	printf("verificando se o array dinamico 'picos_R' esta disponivel no main\n");
	printArrayInt(picos_R, nPicosR);

	pause();

	float freq = getFreq(arqOriginal);	

	printf("freq = %f", freq);

	pause();

	//calcular BPM.
	float BPM;
	for(int i=0;i<nPicosR-1;i++){
		BPM = calculaBPM(freq, picos_R[i+1] - picos_R[i]);
		printf("%i BPM = %f\n", i+1, BPM);
	}

    return 0;
}
