#include <omp.h>
#include <string> 
#include "getRealTime.h"
#define N 1000 //N igual a dimensao da matriz
float a[N][N], b[N][N], c[N][N]; 

//calcula o elemento (i,j) da matriz c (C = A * B)
//C[i][j]=A[i][0]*B[0][j]+...+A[i][n-1]*B[n-1][j]
void calculaElementoMatriz(int dim, int i, int j) { 
    int k, soma = 0.0;
    #pragma omp parallel for
    for(k=0; k<dim; k++) { 
         soma = soma + a[i][k] * b[k][j]; 
    }
    c[i][j] = soma;           
}

int main(){
    fprintf(stderr, "Multiplicacao de Matrizes com OpenMP\n");
    int i, j;
    double inicio , fim, delta;

    // inicializa as matrizes A e B
    int count=1;
    for (i=0;i<N;i++)
  	    for (j=0;j<N;j++){
        	a[i][j]=count;
            b[i][j]=count;
            count++;
        }

    inicio = getRealTime();

    // C = A * B
    #pragma omp parallel for
    for (i=0; i<N; i++) {
        #pragma omp parallel for
        for (j=0; j<N; j++) {
            calculaElementoMatriz(N,i,j);
        }
    }

    fim = getRealTime(); 

    fprintf(stderr, "Tempo gasto = %lf segundos\n", (fim - inicio));
    return(0);
}