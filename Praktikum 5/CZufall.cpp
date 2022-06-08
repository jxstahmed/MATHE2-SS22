#include "CZufall.h"

int CZufall::wert(int a, int b)
{
	int wert = b - a + 1;
	
	return a + (rand() % wert);

}

void CZufall::initialisiere(int s)
{
	srand(s);
}

vector<int> CZufall::test(int a, int b, int N)
{
	vector<int> haufigkeit;

	haufigkeit.resize(b - a + 1);

	for (int i = 0; i < N; i++)
	{
		haufigkeit[wert(a, b) - a]++;
	}

	return haufigkeit;
}

vector<int> CZufall::test_falsch(int a, int b, int N)
{
	vector<int> haufigkeit;

	haufigkeit.resize(b - a + 1);

	for (int i = 0; i < N; i++)
	{
		initialisiere(time(NULL));
		haufigkeit[wert(a, b) - a]++;
	}

	return haufigkeit;
}