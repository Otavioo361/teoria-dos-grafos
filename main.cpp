#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

int m[999][999];
int mi[999][999];
ifstream txtFile;
FILE *arquivo;
void e_simples(int l, int c)
{

	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if (m[i][j] > 1 || m[i][i] > 0)
			{
				fprintf(arquivo, "nao e simples\n");

				return;
			}
		}
	}
}
void zeraMatriz()
{
	for (int i = 1; i <= 100; i++)
	{
		for (int j = 1; j <= 100; j++)
		{
			m[i][j] = 0;
		}
	}
}

void e_conexo(int l, int c)
{
	int ln = 0, cn = 0;

	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			ln = ln + mi[i][j];
			cn = cn + mi[j][i];
		}
		if (ln == 0 || cn == 0)
		{
			fprintf(arquivo, "desconexo");
			fprintf(arquivo,"\n");

			return;
		}
		ln = 0;
		cn = 0;
	}
	fprintf(arquivo, "e Conexo!");
	fprintf(arquivo,"\n");
}
void e_regular(int l, int c)
{
	int z = 0;
	int *x = new int[l];

	for (int i = 1; i <= l; i++)
		x[i] = 0;

	for (int i = 1; i <= l; i++)
		for (int j = 1; j <= c; j++)
			x[i] += m[i][j];

	for (int i = 1; i <= l; i++)
		if ((x[i] == x[i + 1]) && ((i + 1) < l))
			z++;

	if (z == (l - 1))
	{
		fprintf(arquivo, "e Regular!");
		fprintf(arquivo,"\n");

		return;
	}
	else
	{
		fprintf(arquivo, "nao e Regular");
		fprintf(arquivo,"\n");
	}
}
void e_completo(int l, int c)
{
	int z = 0;
	for (int i = 1; i <= l; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if ((m[i][j] == 0) && (i != j))
			{
				z = 1;
			}
		}
	}
	if (z == 1)
	{
		fprintf(arquivo, "nao e completo\n");

		return;
	}
	else
	{
		fprintf(arquivo, "O grafo e completo\n");
	}
}

void verifica_grau(int l)
{
	int totalgrau, grau, i;
	for (i = 1; i <= l; i++)
	{
		grau = 0;
		for (int j = 1; j <= l; j++)
		{
			totalgrau = totalgrau + m[i][j];
			if (m[i][j] >= 1)
				grau = grau + m[i][j];
		}
		fprintf(arquivo, "vertice %d\n", grau);
	}
	fprintf(arquivo, "Soma do grau dos vertices %d\n", totalgrau);
}
void Total()
{
	arquivo = fopen("Total.txt", "w");
	if (arquivo == NULL)
	{
		printf("Nao deu");
		exit(0);
	}
}

int main(int argc, char *argv[])
{

	setlocale(LC_ALL, "Portuguese");

	int vertic, aresta, x, y, cont = 0;

	ifstream txtFile;
	txtFile.open("dados1.txt");

	txtFile >> vertic >> aresta;

	zeraMatriz();

	string data = "";
	while (getline(txtFile, data))
	{
		cont++;
		txtFile >> x >> y;
		m[x][y] = 1;
		m[y][x] = 1;
		mi[cont][x] = 1;
		mi[cont][y] = 1;
		/*if (m[x] == m[x] && m[y] == m[y]) fase de test
		{
			m[x][y] = 2;
		}*/
	}
	Total();

	cout << " " << vertic << " x " << vertic << endl;
	cout << endl;

	for (int i = 1; i <= vertic; i++)
	{
		for (int j = 1; j <= vertic; j++)
		{
			cout << " " << m[i][j] << "  | ";
		}
		cout << endl;
	}
	cout << " " << aresta << " x " << vertic << endl;
	cout << endl;
	for (int i = 1; i <= aresta; i++)
	{
		for (int j = 1; j <=vertic; j++)
		{
			cout << " " << mi[i][j] << "  | ";
		}
		cout << endl;
	}

	cout << endl;

	Total();
	fprintf(arquivo, "Matriz:%d X %d", vertic, vertic);
	fprintf(arquivo, "\n");

	for (int i = 1; i <= aresta; i++)
	{
		for (int j = 1; j <= vertic; j++)

		{
			fprintf(arquivo, " %d |", m[i][j]);
		}
		fprintf(arquivo, "\n");
	}
	fprintf(arquivo, "\n");
	fprintf(arquivo, "Matriz:%d X %d", aresta, vertic);
	fprintf(arquivo, "\n");
	for (int i = 1; i <= vertic; i++)
	{
		for (int j = 1; j <= aresta; j++)

		{
			fprintf(arquivo, " %d |", mi[i][j]);
		}
		fprintf(arquivo, "\n");
	}
	fprintf(arquivo, "\n");

	verifica_grau(vertic);

	e_simples(vertic, aresta);
	e_conexo(vertic, aresta);
	e_regular(vertic, aresta);
	e_completo(vertic, aresta);
	cout << "Arquivos criados com exito" << endl;
	cout << "Fim";

	return 0;
}
