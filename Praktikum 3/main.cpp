#include "C_DGLSolver.h"
#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

static CMyVektor dgls(CMyVektor& y, double x)
{
	return CMyVektor
	{
		2 * y[1] - x * y[0],
		y[0] * y[1] - 2 * x * x * x
	};
}

static double dglsn(CMyVektor& y, double x)
{
	assert(y.get_size() == 3);
	return 2 * x * y[1] * y[2] + 2 * y[0] * y[0] * y[1];
}


int main()
{
	int eingabe = 0;

	while (eingabe != 4)
	{
		cout << "1: Euler-Verfahren" << endl
			 << "2: Heun-Verfahren" << endl
			 << "3: Abweichungen bei DGL" << endl
			 << "4: Zum Beenden" << endl << "Deine Auswahl: ";

		cin >> eingabe;
		cin.ignore();
		cout << endl << endl;


        switch (eingabe)
		{
			case 1:
			{
				C_DGLSolver verfahren(dgls);
				verfahren.euler(0, 2, 100, {0,1}, cout);

			    break;
			}
			case 2:
			{
				C_DGLSolver verfahren(dgls);
				verfahren.heun(0, 2, 100, { 0,1 }, cout);

				break;
			}
			case 3:
			{
				C_DGLSolver verfahren(dglsn);

				CMyVektor y{ 1,-1,2 };
				ofstream keineausgabe = ofstream("/dev/null");
				for (int i = 10; i <= 10000; i *= 10)
				{
					cout << "Abweichung bei Euler bei " << i << " Schritten: " << verfahren.euler(1, 2, i, y, keineausgabe)[0] - 0.5 << endl
						 << "Abweichung bei Heun  bei " << i << " Schritten: " << verfahren.heun(1, 2, i, y, keineausgabe)[0] - 0.5 << endl;
				}
				cout << endl << endl;
				
				break;
			}
			case 4:
			{
				break;
			}

			default:
			{
				cout << "\nDeine Eingabe war leider ungültig\n";
			}
        }
	}
	system("PAUSE");
	return 0;
}