#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include "getRealTime.h"
// #include "fibonnaci_algorithm.h"

const int qtdNum = 500;
__device__ unsigned long long recursiveFibonnaci(int nSize) {
	switch (nSize) {
	case 0:
		return 0;
		break;
	case 1:
		return 1;
		break;
	default:
		return recursiveFibonnaci((nSize - 2)) + recursiveFibonnaci((nSize - 1));
	}
	
}
__global__ void kernel(int *d_sequenciaFib) {
	int i = threadIdx.x;
	d_sequenciaFib[i] = recursiveFibonnaci(i);
	__syncthreads();
}
int main()
{
	double inicio, fim, delta;
	int recursiveFibonnaci[qtdNum];
	int *d_sequenciaFib;

	inicio = getRealTime();

	cudaMalloc((void**)&d_sequenciaFib, qtdNum * sizeof(int));
	kernel << <1, qtdNum >> > (d_sequenciaFib);
	cudaMemcpy(recursiveFibonnaci, d_sequenciaFib, qtdNum * sizeof(int),
		cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();
	inicio = getRealTime();
	for (int i = 0; i < qtdNum; ++i) {
		unsigned long long fibonnaci_ = recursiveFibonnaci[i];
	}

	fim = getRealTime();

	cudaDeviceReset();
	fprintf(stderr, "Tempo gasto = %lf segundos\n", (fim - inicio));
	return 0;
}