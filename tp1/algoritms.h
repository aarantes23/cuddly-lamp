// Adicionar documentação da classe

VerticeGrau grauMinimo(vector<int> ultimoLevel, SparseMatrix<double> matrix, int numVertices)
{
    VerticeGrau result;
    int grau = 0, menorGrau = 0, vertice = 0;

    for (int j = 0; j < numVertices; j++)
    {
        if (matrix.get(ultimoLevel[0], j + 1) != 0)
        {
            grau++;
        }
    }

    menorGrau = grau;
    vertice = ultimoLevel[0];
    grau = 0;

    for (int i = 1; i < ultimoLevel.size(); i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (matrix.get(ultimoLevel[i], j + 1) != 0)
            {
                grau++;
            }
        }
        if (grau <= menorGrau)
        {
            menorGrau = grau;
            vertice = ultimoLevel[i];
        }
        grau = 0;
    }

    result.grau = menorGrau;
    result.vertice = vertice;
    return result;
}

ResutaldoBuscaLargura calculaAltura(int verticeInicial, int numVertices, SparseMatrix<double> matrix)
{

    ResutaldoBuscaLargura result;
    int altura = 0;
    vector<int> fileVertices;
    vector<int> fileVerticesAdj;
    vector<int> resultado;
    bool visitados[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        visitados[i] = false;
    }

    visitados[verticeInicial - 1] = true;

    fileVertices.push_back(verticeInicial);
    resultado.push_back(verticeInicial);
    altura++;
    int cont = 0, contcomprimento = 0;

    while (true)
    {
        for (int i = 0; i < fileVertices.size(); i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                if (matrix.get(fileVertices[i], j + 1) != 0)
                {
                    if (!visitados[j])
                    {
                        resultado.push_back(j + 1);
                        cont++;
                        contcomprimento++;
                        visitados[j] = true;
                        fileVerticesAdj.push_back(j + 1);
                    }
                }
            }
        }

        for (int i = 0; i < fileVerticesAdj.size(); i++)
        {
            fileVertices.push_back(fileVerticesAdj[i]);
        }

        altura++;
        if (fileVertices.size() == numVertices)
        {
            break;
        }
        else
            fileVerticesAdj.clear();
    }

    result.niveis = altura;
    result.ultimoLevel = fileVerticesAdj;

    return result;
}

vector<int> bfs(int verticeInicial, int numVertices, SparseMatrix<double> matrix)
{
    int i;
    queue<int> fila;
    vector<int> resultado;
    bool visitados[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        visitados[i] = false;
    }

    resultado.push_back(verticeInicial);

    visitados[verticeInicial - 1] = true;
    while (true)
    {
        for (int i = 0; i < numVertices; i++)
        {
            if (matrix.get(verticeInicial, i + 1) != 0)
            {
                if (!visitados[i])
                {
                    resultado.push_back(i + 1);
                    visitados[i] = true;
                    fila.push(i + 1);
                }
            }
        }
        if (!fila.empty())
        {
            verticeInicial = fila.front();
            fila.pop();
        }
        else
        {
            break;
        }
    }

    return resultado;
}

int diagonalDominante(int numVertices, SparseMatrix<double> matrix)
{
    vector<double> resultado;
    double diagonalPrincipal, soma = 0;
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (i == j)
            {
                diagonalPrincipal = matrix.get(i + 1, j + 1);
            }
            if (j > i)
            {
                soma += matrix.get(i + 1, j + 1);
            }
        }
        resultado.push_back(fabs(fabs(diagonalPrincipal) - fabs(soma)));
        soma = 0;
    }

    double menor = resultado[0];
    int verticeSelecionado = 0;
    for (int i = 1; i < numVertices; i++)
    {
        if (menor >= resultado[i])
        {
            menor = resultado[i];
            verticeSelecionado = i;
        }
    }

    return verticeSelecionado + 1;
}

int georgeLiu(int numVertices, SparseMatrix<double> matrix)
{
    ResutaldoBuscaLargura bfsV;
    ResutaldoBuscaLargura bfsU;

    int u = 0, minimo_u;
    int v = rand() % ((numVertices + 1) - 1) + 1;
    bfsV = calculaAltura(v, numVertices, matrix);

    do
    {
        u = grauMinimo(bfsV.ultimoLevel, matrix, numVertices).vertice;
        bfsU = calculaAltura(u, numVertices, matrix);
        if (bfsU.niveis > bfsV.niveis)
        {
            v = u;
            bfsV = bfsU;
        }
    } while (bfsU.niveis != bfsV.niveis);
    return v;
}

int larguraDeBanda(int numVertices, SparseMatrix<double> matrix, vector<int> bfs)
{
    int cont = 0;
    int maior = 0;
    int linha = 0;

    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if ((i >= j) and (matrix.get(bfs[(numVertices - 1) - i], bfs[(numVertices - 1) - j]) != 0))
            {
                cont++;
            }
        }
        if (cont > maior)
        {
            maior = cont;
            linha = i;
        }
        cont = 0;
    }

    return linha;
}
