#ifndef ANDRE_H_INCLUDED
#define ANDRE_H_INCLUDED

#define MAX 10

//////////////////////////////////////
// FUNCOES REAPROVEITADAS DAS AULAS // 
//////////////////////////////////////
float maior(float a, float b);
int contaLinhas(char * fileName);
void printArrayFloat(float *arr, int size);
void printArrayInt(int *arr, int size);
///////////////////////////////////////
// FUNCOES ESPECIFICAS DESTE PROJETO // 
///////////////////////////////////////

//gera os nomes dos arquivos
void geraNomes(char * amostras, char * arqOriginal, char * arqFiltrado);

//le todas as amostras do ECG e armazena num vetor dinamico
float * leAmostras(char * nomeArquivo, int nLinhas);


//funcoes para determinar qual eh o valor de referencia para encontrar os picos R
float maiorVet(float *vet, int tamanho);

float mediaVetRecursiva(float *vet, int tamanho, int ctrl);


//conta e gera vetor de picosR
int maiorValorVetIndex(float *, int);

int contaPicosR(float * vetECG, int tamanhoECG, float pico_R_referencia);

int * geraPicosR(float * vetECG, int tamanhoECG, float pico_R_referencia, int nPicosR);



//Pega a frequencia do arquivo
int searchChar(char * str, char ch);

float findFreq(char * strFreq);

float getFreq(char * nomeArquivo);



//calcula todos os batimentos por minuto entre os picos R
float calculaBPM(float freq, int dist_pontos);

void pause();


#endif /* ANDRE_H_INCLUDED */