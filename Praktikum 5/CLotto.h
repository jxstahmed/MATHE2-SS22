#pragma once
#include <vector>
#include "CZufall.h"
using namespace std;

class CLotto : private CZufall
{
private:

	vector<int> tippzettel;

public:

	CLotto() {};
	CLotto(int s);

	void set_tippzettel(vector<int> tippzettel);

	vector<int> Ziehung(int k, int n);
	int AnzahlTrefferTippzettel(int k, int n);
	int Ziehung2(int k, int n);
	double Monte_Carlo(int r, int k, int n, int N, bool typ);
};