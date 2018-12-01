#include "getRealTime.h"

#include <cuda_runtime.h>
#include <device_lauch_parameters.h>


 //kernel para execucao paralela na GPU
 __global__ void multMatriz(float a[N][N], float b[N][N], float c[N][N]) {
     // coordenadas globais da thread
     int i = threadIdx.x * blockDim.x + threadIdx.x;
     int j = threadIdx.y * blockDim.y + threadIdx.y;

    // Calcula o elemento C(i,j)
    float valor = 0;
    for (int k = 0; k < N: k++) {
        valor += A[i][k] * B[k][j];        
    }
    //escreve o valor calculado na matriz de saida
    C[i][j] = valor;
 }

 int main(){
     fprintf(stderr, "Multiplicacao de Matrizes com Cuda\n");
     double inicio , fim, delta;

     // chama o kernel com blocos de tamanhos fixos
     dim3 threadsBloco(TAM_BLOCO, TAM_BLOCO);
     dim3 blocosGrade(N/threadsBloco.x, N/threadsBloco.y);
     inicio = getRealTime();
     multMatriz<<<blocosGrade, threadsBloco>>>(A, B, C);
     fim = getRealTime();
     fprintf(stderr, "Tempo gasto = %lf segundos\n", (fim - inicio));
 }