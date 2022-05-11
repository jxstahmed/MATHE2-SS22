#include "C_DGLSolver.h"
#include <iostream>

using namespace std;


C_DGLSolver::C_DGLSolver(DGLSystem DGL_System)
{
	mn = false;
	art.erster = DGL_System;
}

C_DGLSolver::C_DGLSolver(DGLSystemN DGL_SystemN)
{
	mn = true;
	art.n = DGL_SystemN;
}

CMyVektor C_DGLSolver::ableitungen(CMyVektor& y, double x)
{
	if (!mn)
	{
		return art.erster(y, x);
	}
	else
	{
		CMyVektor ergebnis(y.get_size());

		for (int i = 0; i < y.get_size() - 1; i++)
		{
			ergebnis[i] = y[i + 1];
		}
		ergebnis[y.get_size() - 1] = art.n(y, x);

		return ergebnis;
	}
}

CMyVektor C_DGLSolver::euler(double x_start, double x_end, double schritt, const CMyVektor& y_start, ostream& ausgabe)
{
	const double delta = (x_end - x_start) / schritt;

	CMyVektor y(y_start.get_size());
	CMyVektor y_alt = y_start;

	ausgabe << "h = " << delta << endl << endl << endl;

	for (int i = 0; i < schritt; i++)
	{
		CMyVektor aby = ableitungen(y_alt, x_start);

		ausgabe << "Schritt " << i << ":" << endl
			 << "\tx = " << x_start << endl
			 << "\ty = " << y_alt << endl
			 << "\ty' = " << aby << endl << endl;

		y = y_alt + delta * aby;
		x_start += delta;
		y_alt = y;
	}

	ausgabe << "Ende bei" << endl
	  	 << "\tx = " << x_start << endl
		 << "\ty = " << y_alt << endl << endl << endl;

	return y_alt;
}

CMyVektor C_DGLSolver::heun(double x_start, double x_end, double schritt, const CMyVektor& y_start, ostream& ausgabe)
{
	const double delta = (x_end - x_start) / schritt;

	double alt_x;

	CMyVektor y_test = y_start;
	CMyVektor y(y_start.get_size());
	CMyVektor y_mittel(y_start.get_size());
	CMyVektor aby_test(y_start.get_size());

	ausgabe << "h = " << delta << endl << endl << endl;

	for (int i = 0; i < schritt; i++)
	{
		y = y_test;

		CMyVektor aby(y_start.get_size());
		aby = ableitungen(y, x_start);

		ausgabe << "Schritt " << i << ":" << endl
			 << "\tx = " << x_start << endl
			 << "\ty = " << y << endl
			 << "\ty'_orig = " << aby << endl << endl;


		y_test = y_test + delta * ableitungen(y_test, x_start);
		alt_x = x_start;
		x_start += delta;
		aby_test = ableitungen(y_test, x_start);
		y_mittel = 0.5 * (ableitungen(y, alt_x) + aby_test);

		ausgabe << "\ty_Test = " << y_test << endl
			 << "\ty'_Test = " << aby_test << endl << endl
			 << "\ty'_Mittel = " << y_mittel << endl << endl;

		y_test = y + delta * y_mittel;
	}

	ausgabe << "Ende bei" << endl
		<< "\tx = " << x_start << endl
		<< "\ty = " << y_test << endl << endl << endl;

	return y_test;
}