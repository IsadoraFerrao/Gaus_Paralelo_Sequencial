// Algoritmo de Gauss-Legendre - Cálculo do número PI
// Universidade de Sao Paulo - Sistemas Operacionais (2019)

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>

#define PRECISAO 10 //precisao utilizada para o calculo

long long int NUM_PONTOS;
long int numThreads;

float pi_final=0.0;
pthread_mutex_t mutexSum; //variavel mutexsum do tipo pthread_mutex
int indice = PRECISAO;
long long total_all=0;

double a(int indice);
double b(int indice);
double t(int indice);
double p(int indice);

void *pi(void *threadid){
    double pi_1, pi_2, pi;
    double k = 0;
    long long int chunk;
    double j = 0;
    chunk = NUM_PONTOS/numThreads; //divide os pedacos de execucao entre as threads disponiveis
    for(j=0;j<chunk;j++){
        pi_1 = (pow(a(indice) + b(indice), 2)); //parte superior da formula
        pi_2 = 4 * t(indice);
        pi = pi_1/pi_2;
     }
    
    //para tratar a sincronizacao utilizamos o bloqueio mutex
    
	pthread_mutex_lock(&mutexSum);   //bloqueia um objeto mutex
	pi_final += pi;
	pthread_mutex_unlock(&mutexSum); //libera um objeto mutex

	return NULL;
}

double a(int indice){
    if (indice == 0){ //a0 = 1
        return 1;
    }
    else{
        return (a(indice-1) + b(indice-1)) / 2; //a(n+1) = a(n) + b(n)/2
    }
}

double b(int indice){
    if(indice == 0){
        return 1/sqrt(2);
    }
    else{
        double b1, b2;
        b1 = (a(indice-1) * b(indice-1));
        b2 = sqrt(b1);
        return b2; // b(n+1) = sqrt(a(n) - a(n+1)) ^ 2
    }
}

double t(int indice){
    if(indice == 0){
        return 0.25;
    }
    else{
        return t(indice-1) - p(indice-1) * pow(a(indice-1) - a(indice),2); // t(n+1) = t(n) - p(n)(a(n) - a(b+1)^2)
    }    
}

double p(int indice){
    if(indice == 0){
        return 1;
    }
    else{
        return 2 * p(indice-1); //p(n+1) = 2p(n)
    }
}


int main(int argc, char **argv){

    FILE *saida;
    saida = fopen("tempo.txt", "a");

	if (argc < 2) {
		printf ("Errado! Utilize: programa <threads> <input-size>\n\n \tE.g. -> ./programa 2 400000\n\n");
		exit(1);
	}

    /* TRATANDO AS ENTRADAS */
    
	NUM_PONTOS = strtoul(argv[2], NULL, 10); //n de iteracoes
	long int i;
	numThreads = atol(argv[1]);
	pthread_t threads[numThreads]; //vetor de threads do tipo pthread

    //Coleta de tempo
    clock_t start_t, end_t;
    double total_t;
    start_t = clock(); //Coleta Inicio
    
    /* CRIA A THREAD */
	for(i=1;i<=numThreads;i++){
		pthread_create(&threads[i], NULL, pi, (void *)i); 
	}
	
	/* RECEBE A ESTRUTURA DE CONTROLE DA THREAD */
	
	for(i=1;i<=numThreads;i++){
		pthread_join(threads[i], NULL); 
	}
	
	pi_final = pi_final/numThreads;
    end_t = clock(); //Coleta Final
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    /*RESULTADO*/
	printf("Pi = %lf\n", pi_final);	
    fprintf(saida, "%f\n", total_t);
	return 0;

}
