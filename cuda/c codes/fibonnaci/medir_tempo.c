#include <time.h>
//retorna o instante de tempo atual em segundos 
double tempoAtual() {
	struct timespec tempo;
	clock_gettime(CLOCK_MONOTONIC_RAW , &tempo); 
	return tempo.tv_sec + tempo.tv_nsec /1000000000.0;
}

void main(){
	double inicio , fim, delta;
	inicio = tempoAtual();
	//...trecho do programa que queremos medir o tempo 
	fim = tempoAtual(); 
	//tempo consumido para executar o trecho do programa
	delta = fim - inicio;
}
	