#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getRealTime.h"
#include "fibonnaci_algorithm.h"

int main(int argc, char *argv[]) {

    int d = 50;
    printf("[Sequencial] Calcula Fibonnaci de 0 a %d, retorna o tempo gasto\n",d);
    int num;    
    double inicio , fim, delta;
    
    inicio = getRealTime();
    for (num = 0; num <= d; num++) {
        //fprintf(stderr,"Fibonnaci de %d = ", num);
        unsigned long long fibonnaci = recursiveFibonnaci(num);
        //printf("%llu",fibonnaci);
    }
    fim = getRealTime(); 

    fprintf(stderr, "N= %d \nTempo gasto = %lf segundos\n", d,(fim - inicio));
    return 0;
}
