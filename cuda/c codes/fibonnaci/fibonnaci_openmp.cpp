#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getRealTime.h"
#include "fibonnaci_algorithm.h"

int main(int argc, char ** argv) {
        
    printf("[OpenMP] Calcula Fibonnaci de 0 a 50, retorna o tempo gasto.\n");
    int num;
    double inicio , fim, delta;
    
    inicio = getRealTime();

    #pragma omp parallel private(num)
    {
        #pragma omp for schedule(dynamic, 1)
        for (num = 0; num <= 50; num++) {
            //fprintf(stderr,"Fibonnaci de %d = ", num);
            unsigned long long fibonnaci = recursiveFibonnaci(num);
            //printf("%llu",fibonnaci);
        }
    }
   
    fim = getRealTime(); 

    fprintf(stderr, "Tempo gasto = %lf segundos\n", (fim - inicio));
    return 0;
}