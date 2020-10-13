#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#define TAM 10
#define P 20
#define UMBRL 0.75

using namespace std;

int distan[TAM][TAM];
vector<int>* poblacion[P];
vector<int>* temp[P];
vector<int> ciudades,solucion,aptitud;

ifstream matriz("m_ciudades.txt");
ofstream salida("rutas.txt");

using namespace std;


int calcu_mejor()
{
	int mejor = 0;
	int m_ = 1000000;
	for (int i=0;i<P;i++)
		if (m_ > aptitud[i]) {
			m_ = aptitud[i];
			mejor = i;
		}
	return mejor;
}

float calcu_promedio()
{
	float prom=0;
	for (int i=0;i<P;i++)
    {
        prom+=aptitud[i];
    }
	return prom/(float)P;
}

int calcu_aptitud(vector<int>* p)
{
	int sm = 0;
	for (int i = 1; i < p->size(); ++i)
    {
        sm+= distan[p->at(i)][p->at(i - 1)];
    }
	sm+= distan[p->at(p->size() - 1)][p->at(0)];
	return sm;
}

void verRuta(vector<int>* r)
{
	for (int i=0; i<r->size();++i)
    {
        cout << r->at(i) << " ";
    }
}

void cruce(vector<int>* padre1, vector<int>* padre2, vector<int>* hijo) {
	int j;
	for (int i = 0; i < padre1->size()/2; ++i) {
		j = i;
		while (j < 10 && padre2->at(i) != padre1->at(j))
			j++;
		if (j < 10) {
			if (hijo->at(i) < 0)
				hijo->at(j) = padre1->at(i);
			else
				hijo->at(j) = hijo->at(i);
			hijo->at(i) = padre2->at(i);
		}
		else
			if (hijo->at(i) < 0)
				hijo->at(i) = padre1->at(i);
	}
	for (int i = padre1->size()/2; i < padre1->size(); ++i)
    {
		if (hijo->at(i) < 0)
		{
		    hijo->at(i) = padre1->at(i);
		}

	}
}

void mutacion(vector<int>* v) {
	int cambiar;
	random_shuffle(ciudades.begin(), ciudades.end());
	cambiar = v->at(ciudades[0]);
	v->at(ciudades[0]) = v->at(ciudades[1]);
	v->at(ciudades[1]) = cambiar;
}

int main()
{

	srand(time(NULL));
	for (int i = 0; i < TAM; ++i)
    {
        ciudades.push_back(i);
    }
	for (int i = 0; i < P; ++i)
    {
        solucion.push_back(i);
    }
	for (int i = 0; i < P; ++i)
    {
		vector<int>* p = new vector<int>;
		random_shuffle(ciudades.begin(),ciudades.end());
		for (int j=0; j<TAM; ++j)
			p->push_back(ciudades[j]);
		poblacion[i] = p;
	}

	if (matriz.is_open())
	{
		for (int i = 0; i < TAM; ++i)
			for (int j = 0; j < TAM; ++j)
				matriz >> distan[i][j];
		matriz.close();
	}

	////////////////////////////
	int a, b, m;
	float t;
	int cant_r=50;
	for (int ciclo=0;ciclo<cant_r; ++ciclo) {

		aptitud.clear();

		for (int i=0;i<P;i++)
        {
            aptitud.push_back(calcu_aptitud(poblacion[i]));
        }

		m = calcu_mejor();
		cout << "Mejor RUTA: ";
		verRuta(poblacion[m]);
		cout << "  |    Long(APTITUD): " << aptitud[m];
		cout <<"   |    Promedio: "<<calcu_promedio()<<endl;

		if (salida.is_open())
        {
            salida <<aptitud[m]<<"\t"<<calcu_promedio() << endl;
        }

		for (int i = 0; i < 17; ++i)
        {
			random_shuffle(solucion.begin(), solucion.end());
			t = ((double)rand()/(RAND_MAX));
			if (t < UMBRL)
            {
				aptitud[solucion[0]] < aptitud[solucion[1]] ? a = 0 : a = 1;
				aptitud[solucion[2]] < aptitud[solucion[3]] ? b = 2 : b = 3;
			}
			else
			{
				aptitud[solucion[0]] > aptitud[solucion[1]] ? a = 0 : a = 1;
				aptitud[solucion[2]] > aptitud[solucion[3]] ? b = 2 : b = 3;
			}

			temp[i] = new vector<int>;
			for (int k=0;k<TAM;k++)
            {
                temp[i]->push_back(-1);
            }
			cruce(poblacion[solucion[a]], poblacion[solucion[b]], temp[i]);
		}

		temp[17] = new vector<int>;
		for (int i = 0; i < TAM; ++i)
        {
            temp[17]->push_back(poblacion[m]->at(i));
        }

		random_shuffle(solucion.begin(), solucion.end());
		temp[18] = poblacion[solucion[0]];
		temp[19] = poblacion[solucion[1]];
		mutacion(temp[18]);
		mutacion(temp[19]);

		for (int i=0;i<P;i++)
        {
            poblacion[i]=temp[i];
        }
	}
	salida.close();
	return 0;
}

