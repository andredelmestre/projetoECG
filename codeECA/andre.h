#ifndef ANDRE_H_INCLUDED
#define ANDRE_H_INCLUDED

#define MAX 10

//TADs

float maior(float a, float b);
float maiorVet(float *vet, int tamanho);
int maiorValorVetIndex(float *, int);


float mediaVet(float *vet, int tamanho);
float mediaVetRecursiva(float *vet, int tamanho, int ctrl);



int procuraZonaR(float * vetECG, int tamanho, int * inicio_pico_R, int * fim_pico_R, float valorInteresse);
float calculaBPM(float freq, int dist_pontos);
float calcBPM(int dist_pontos, float freq);


#endif /* ANDRE_H_INCLUDED */
