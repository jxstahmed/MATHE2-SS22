#pragma once
#include<vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

class CZufall
{
public:

	int wert(int a, int b);
	void initialisiere(int s);
	vector<int> test(int a, int b, int N);
	vector<int> test_falsch(int a, int b, int N);
};