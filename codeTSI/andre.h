#ifndef ANDRE_H_INCLUDED
#define ANDRE_H_INCLUDED

#define MAX 10

//TADs

float maior(float a, float b);
float maiorVet(float *vet, int tamanho);
int maiorValorVetIndex(float *, int);

float mediaVet(float *vet, int tamanho);
float mediaVetRecursiva(float *vet, int tamanho, int ctrl);


int identificaPicosR(float * vetECG, int tamanhoECG, int * inicioZonaInteresse, int * fimZonaInteresse, float pico_R_referencia);

float calculaBPM(float freq, int dist_pontos);


#endif /* ANDRE_H_INCLUDED */