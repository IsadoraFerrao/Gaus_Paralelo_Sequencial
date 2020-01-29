// Algoritmo de Gauss-Legendre - Cálculo do número PI
// Universidade de Sao Paulo - Sistemas Operacionais (2019)

#include <stdio.h>
#include <math.h>
#include<time.h>

#define PRECISAO 10 //precisao utilizada para o calculo

double a(int indice);
double b(int indice);
double t(int indice);
double p(int indice);

double pi(int indice){
    double pi_1, pi_2, pi;
    int iter = 1000000000; //numero de iteracoes para computar a formula
    double k = 0;
    
    for (k = 0; k < iter; k++){ 
        pi_1 = (pow(a(indice) + b(indice), 2)); //parte superior da formula
        pi_2 = 4 * t(indice);
        pi = pi_1/pi_2;
    }
    return  pi;
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


int main(){ 
    double resp;
    FILE *saida;
    saida = fopen("tempo.txt", "a");
    
    //Coleta de tempo
    clock_t start_t, end_t;
    double total_t;
    start_t = clock(); //Coleta Inicio*/
    
    resp = pi(PRECISAO);
    
    printf("PI de Gauss = %f \n", resp);
    
	end_t = clock(); //Coleta Final
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    fprintf(saida, "%f\n", total_t);
    return 0;


}
