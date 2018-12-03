// Adicionar documentação da classe
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <list>
#include <vector>
#include <queue>
#include <math.h>
#include <dirent.h>
#include <omp.h>

#include "libs/SparseMatrix/SparseMatrix.cpp"
#include "libs/Tempo/getRealTime.h"
#include "libs/obj/objs.h"
#include "algoritms.h"

using namespace std;

int main()
{

    double startTime, endTime, spendTime_g, spendTime_d;
    ResutaldoBuscaLargura result;
    vector<int> resultado;
    int vertice, l, c, altura, numLinhas, numColunas, instancias;

    // Tratamento dos arquivos
    char url[512] = "";
    char aux[512] = "";
    char db_[512] = "dbs";

    int georgeLiu_;
    int diagonalDominante_; // Salva resultado final

    DIR *dir;
    struct dirent *lsdir;
    dir = opendir("dbs");

    printf("base,linhas,colunas,instancias,largura_inicial,gl_tempo,gl_largura_final,dd_tempo,dd_largura_final\n");

    // Calcula a largura de banda para todos os arquivos da pasta "dir"
    while ((lsdir = readdir(dir)) != NULL)
    {
        strncpy(url, lsdir->d_name, 128); //printf("%s\n",url);// Base atual

        if ((!strcmp(".", url) || !strcmp("..", url)) == 0)
        {
            char caminho[512] = "";

            strcat(caminho, "dbs");
            strcat(caminho, "/");
            strcat(caminho, url);

            ifstream arq(caminho, ios::in); // Associa o arquivo a variavel

            if (!arq)
            {
                cout << "Erro ao abrir o arquivo: " << url << endl;
                return 1;
            }

            while (arq.peek() == '%')
                arq.ignore(2048, '\n'); // Ignora as linhas de comentarios
            arq >> numLinhas >> numColunas >> instancias;
            int numValores = numLinhas * numColunas;
            SparseMatrix<double> matrix(numLinhas); // Matrix do CRS Sparse-Matrix
            double valores[instancias][3];

            for (l = 0; l < instancias; l++)
            { // Armazena os dados do arquivo em um vetor de inteiros
                for (c = 0; c < 3; c++)
                {
                    arq >> valores[l][c];
                }
            }

            arq.close();

            for (l = 0; l < instancias; l++)
            { // Preenche a matrix do formato CRS com os valores do vetor
                matrix.set((valores[l][2]), (valores[l][0]), (valores[l][1]));
                matrix.set((valores[l][2]), (valores[l][1]), (valores[l][0]));
            }

            // Calcula a largura de banda inicial, sem nenhum dos algoritmos
            resultado = bfs(numColunas, numLinhas, matrix);
            int larguraInicial = larguraDeBanda(numLinhas, matrix, resultado);

            for (int a = 0; a < 2; a++)
            {
                srand(time(NULL));
                int vertice_;
                if (a == 0)
                { //printf("GeorgeLiu\n");
                    startTime = getRealTime();
                    vertice_ = georgeLiu(numLinhas, matrix);
                    endTime = getRealTime();
                    spendTime_g = endTime - startTime;
                }
                else
                { //printf("Diagonal Dominante\n");
                    startTime = getRealTime();
                    vertice_ = diagonalDominante(numLinhas, matrix);
                    endTime = getRealTime();
                    spendTime_d = endTime - startTime;
                }

                // Calcula a largura de banda final depois dos algoritmos
                resultado = bfs(vertice_, numLinhas, matrix);
                int linha = larguraDeBanda(numLinhas, matrix, resultado);
                if (a == 0)
                {
                    georgeLiu_ = linha;
                }
                else
                {
                    diagonalDominante_ = linha;
                }
            }
            // Mostra os resultados
            printf("%s,%d,%d,%d,%d,%lf,%d,%lf,%d\n",
                   url, numLinhas, numColunas, instancias, larguraInicial,
                   spendTime_g, georgeLiu_, spendTime_d, diagonalDominante_);
        } // End if inicial
    }     // End while
    printf("-----------------------------------------------------\n");
}
