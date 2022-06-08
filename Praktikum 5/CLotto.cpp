#include "CLotto.h"
#include <stdlib.h>
#include <time.h>
using namespace std;


CLotto::CLotto(int s)
{
	if (s < 0)
	{
		initialisiere(time(NULL));
	}
	else
	{
		initialisiere(s);
	}
}

void CLotto::set_tippzettel(vector<int> tippzettel)
{
	this->tippzettel = tippzettel;
}

vector<int> CLotto::Ziehung(int k, int n)
{
	vector<int> ziehung;
	bool gezogen = false;

	for (int i = 0; i < k; i++)
	{
		int x = wert(1, n);

		for (int j = 0; j < ziehung.size(); j++)
		{
			//Wenn Zahl bereits gezogen.
			if (ziehung[j] == x)
			{
				i--;
				gezogen = true;
				break;
			}
		}

		if (gezogen == false)
		{
			ziehung.push_back(x);
		}

		gezogen = false;
	}

	return ziehung;
}

int CLotto::AnzahlTrefferTippzettel(int k, int n)
{
	vector<int> ziehung = Ziehung(k,n);
	int richtig = 0;

	for (int i = 0; i < int(this->tippzettel.size()); i++)
	{
		for (int j = 0; j < int(ziehung.size()); j++)
		{
			if (this->tippzettel[i] == ziehung[j])
			{
				richtig++;
			}
		}
	}
	return richtig;
}


int CLotto::Ziehung2(int k, int n)
{
	vector<int> ziehung1 = Ziehung(k, n);
	vector<int> ziehung2 = Ziehung(k, n);
	int count = 0;

	for (int i = 0; i < int(ziehung1.size()); i++)
	{
		for (int j = 0; j < int(ziehung2.size()); j++)
		{
			if (ziehung1[i] == ziehung2[j])
				count++;
		}
	}
	return count;
}

double CLotto::Monte_Carlo(int r, int k, int n, int N, bool typ)
{
	int richtig = 0;
	if (typ)
	{
		for (int i = 0; i < N; i++)
		{
			if (this->AnzahlTrefferTippzettel(k, n) == r)
			{
				richtig++;
			}
		}
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			if (this->Ziehung2(k, n) == r)
			{
				richtig++;
			}
		}
	}
	return double(richtig) / N * 100;
}