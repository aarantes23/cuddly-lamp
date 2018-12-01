#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>
#include "getRealTime.h"
#define tamBloco 16

__global__ void matrixMult(float *A, float *B, float *C, int N)
{
	//Multiplicação de matrix C=A*B de tamanho NxN
	//Cada thread computa um único elemento da matrix C
	int linha = blockIdx.y*blockDim.y + threadIdx.y;
	int coluna = blockIdx.x*blockDim.x + threadIdx.x;
	float sum = 0.f;
	for (int n = 0; n < N; ++n)
		sum += A[linha*N + n] * B[n*N + coluna];
	C[linha*N + coluna] = sum;
	__syncthreads();
}
int main()
{
	double inicio, fim;
	int N, K;
	K = 1000;
	N = K * tamBloco;
	//Criando matrizes no host
	float *hA, *hB, *hC;
	hA = new float[N*N];
	hB = new float[N*N];
	hC = new float[N*N];
	//Iniciando matrizes
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			hA[j*N + i] = 2.f*(j + i);
			hB[j*N + i] = 1.f*(j - i);
		}
	}
	//Criando as matrizes no device
	float *dA, *dB, *dC;
	cudaMalloc((void**)&dA, N*N * sizeof(float));
	cudaMalloc((void**)&dB, N*N * sizeof(float));
	cudaMalloc((void**)&dC, N*N * sizeof(float));
	dim3 threadBlock(tamBloco, tamBloco);//threads = 16x16
	dim3 grid(K, K);//blocos = KxK

	//Copiando as matrizes do host para o device
	cudaMemcpy(dA, hA, N, cudaMemcpyHostToDevice);
	cudaMemcpy(dB, hB, N, cudaMemcpyHostToDevice);

	inicio = getRealTime();	
	//execução do kernel
	matrixMult << <grid, threadBlock >> > (dA, dB, dC, N);
	fim = getRealTime();
	//Copia o resultado do device para cpu
	cudaMemcpy(hC, dC, N*N * sizeof(float), cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();
	cudaDeviceReset();

	
	fprintf(stderr, "Tamanho = %d\nTempo gasto = %lf segundos\n", K,(fim - inicio));
	return 0;
}