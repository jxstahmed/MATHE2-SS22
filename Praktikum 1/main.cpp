#include "CMyVektor.h"
#include <iostream>

using namespace std;

double f(const CMyVektor& x)
{
	return sin(x[0] * x[1]) + sin(x[0]) + cos(x[1]);
}

double g(const CMyVektor& x)
{
	return -(2 * (x[0] * x[0]) - 2 * x[0] * x[1] + (x[1] * x[1]) + (x[2] * x[2]) - 2 * x[0] - 4 * x[2]);
}

int main()
{
	///*
	// Funktion F
	CMyVektor ff(2);

	ff.set_Value(0, 0.2);
	ff.set_Value(1, -2.1);

	maximierung(ff, f);

	//*/

	/*
	// Funktion G
	CMyVektor gg(3);

	gg.set_Value(0, 0);
	gg.set_Value(1, 0);
	gg.set_Value(2, 0);

	maximierung(gg, g, 0.1);

	*/

	cout << endl;
	system("PAUSE");
}