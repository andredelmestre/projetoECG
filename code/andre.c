#include <stdio.h>
#include <stdlib.h>
#include "andre.h"


void pause(){
	printf("\n\n###################################################\n\n");
	getchar();
}

float maior(float a, float b){
	if(a>b)
		return a;
	else
		return b;
}

int contaLinhas(char * fileName){
    // a ser desenvolvido em aula
    FILE *fp;
    char ch;
    int cont=1;
    fp = fopen(fileName, "r");
    if(fp==NULL){
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }
    while( !feof(fp) ){
        ch = fgetc(fp);
        if (ch == '\n')
            cont++;
    }
    fclose(fp);
    return cont;
}

void printArrayInt(int *arr, int size){
    printf("Tamanho do array: %i \n\n", size);

    printf("Array: ");
    for (int i = 0; i < size; i++){
        // *(ptr + i) is equivalent to arr[i]
        printf("%d, ", *(arr + i));
    }
    printf("\n\n");
}

void printArrayFloat(float *arr, int size){
    printf("Tamanho do array: %i \n\n", size);

    printf("Array: ");
    for (int i = 0; i < size; i++){
        // *(ptr + i) is equivalent to arr[i]
        printf("%f, ", *(arr + i));
    }
    printf("\n\n");
}

void geraNomes(char * amostras, char * arqOriginal, char * arqFiltrado){
	char nomeFiltrado[40]="../plot/";
	char nomeOriginal[30]="../plot/";

	strcat(nomeOriginal, amostras);
	strcat(nomeOriginal, ".txt");

	strcat(nomeFiltrado, amostras);
	strcat(nomeFiltrado, "_filtered.txt");

	strcpy(arqOriginal, nomeOriginal);
	strcpy(arqFiltrado, nomeFiltrado);
}

float * leAmostras(char * nomeArquivo, int nSamples){
	float * samples = (float *) malloc(sizeof(float)*nSamples);
	if (samples == NULL){ printf("erro ao alocar memoria\n"); return NULL;	}

	FILE *fp = fopen(nomeArquivo, "r");
	if (fp == NULL){ printf("erro de LEITURA ao abrir arquivo %s\n", nomeArquivo); return NULL;	}
	int i=0;

	printf("\nIniciando a LEITURA do arquivo %s\n", nomeArquivo);

    while( !feof(fp) ){
        fscanf(fp, "%f", samples+i);
        i++;
    }
    
    fclose(fp);

    return samples;
}


float getFreq(char * nomeArquivo){
    char str[40], *result;

	FILE *fp = fopen(nomeArquivo, "r");
	if (fp == NULL){ printf("erro de LEITURA ao abrir arquivo %s\n", nomeArquivo); return 0.0;	}
	printf("\nIniciando a LEITURA do arquivo %s\n", nomeArquivo);

	result = fgets(str, 40, fp);
	result = fgets(str, 40, fp);
	// a informacao que quero esta na segunda linha do arquivo

	float freq = findFreq(str);

    fclose(fp);

    return freq;
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

// para entender a recursao abaixo, assuma o seguinte vetor:
// [0]		4
// [1]		6
// [2]		8
// media recursiva usa 4/3 + 6/3 + 8/3 = 6
// media que estamos acostumados usa (4+6+8)/3 = 6
float mediaVetRecursiva(float *vet, int tamanho, int ctrl){
	if( ctrl >= tamanho){
		return 0 ;
	}else{
		return *vet / tamanho + mediaVetRecursiva(vet+1, tamanho, ctrl+1);
	}
}

int searchChar(char * str, char ch){
	for (int i = 0; i < strlen(str); ++i)
		if(ch == *(str+i) ){
			return i;
		}
	return -1;
}


float findFreq(char * strFreq){
	int pos = searchChar(strFreq, '=');
	char *ptr_ch = strFreq+pos+2; // primeiro digito
	int freq=0;

	while( *ptr_ch >='0' && *ptr_ch <='9'){
		freq += searchChar("0123456789", *ptr_ch);
		ptr_ch++;
		freq *= 10;
	}
	freq /= 10;

	// printf("#############\n");
	// printf("## freq = %i\n", freq);

	ptr_ch++;
	float freqSaida = freq;
	freq = 0;

	while( *ptr_ch >='0' && *ptr_ch <='9'){
		freq += searchChar("0123456789", *ptr_ch);
		ptr_ch++;
		freq *= 10;
	}
	freq /= 10;

	freqSaida = freqSaida + freq*0.01; //freqSaida.freq

	// printf("#############\n");
	// printf("## freq = %i\n", freq);
	// printf("## freqSaida = %.2f\n", freqSaida);
	// printf("#############\n");

	return freqSaida;
}

//retornar o num de picos R do vetor vetECG
int contaPicosR(float * vetECG, int tamanhoECG, float pico_R_referencia){
	int i, contaPicos=0, flagInteresse=0;
	for(i=0; i<tamanhoECG; i++){
		if( * (vetECG + i) > pico_R_referencia && flagInteresse == 0){
			flagInteresse = 1;
		}else if( * (vetECG + i) < pico_R_referencia  && flagInteresse == 1) {
			flagInteresse = 0;
			contaPicos++;
		}
	}
	return contaPicos;
}

int * geraPicosR(float * vetECG, int tamanhoECG, float pico_R_referencia, int nPicosR){
	int i, teste, flagInteresse=0, inicioZonaInteresse, fimZonaInteresse, r=0;
	
	int * picos_R = (int *) malloc(sizeof(int) * nPicosR);
	if (picos_R == NULL){ printf("erro ao alocar memoria\n"); return NULL;	}

	for(i=0; i<tamanhoECG; i++){
		if( * (vetECG + i) > pico_R_referencia && flagInteresse == 0){
			inicioZonaInteresse = i;
			flagInteresse = 1;
			// printf("inicioZonaInteresse = %i\n", inicioZonaInteresse);
		}else if( * (vetECG + i) < pico_R_referencia  && flagInteresse == 1) {
			fimZonaInteresse = i;
			flagInteresse = 0;
			// printf("fimZonaInteresse = %i\n", fimZonaInteresse);

			picos_R[r] = maiorValorVetIndex(vetECG + inicioZonaInteresse, fimZonaInteresse-inicioZonaInteresse);
			// printf("picos_R[%i] = %i -- %i\n", r, picos_R[r], inicioZonaInteresse+picos_R[r]);
			picos_R[r] += inicioZonaInteresse;
			r++;
		}
	}
	// return NULL;
	return picos_R;
}

float calculaBPM(float freq, int dist_pontos){
	float umaBatida = dist_pontos / freq;
	float BPM = 60/umaBatida;
	return BPM;
}
