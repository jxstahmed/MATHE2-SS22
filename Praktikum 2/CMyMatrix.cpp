#include "CMyMatrix.h"
using namespace std;


void CMyMatrix::set_dim(int x, int y)	//Dimension und Vektor größe nachträglich ändern.
{
	dim = { x,y };
	wert.resize(x * y);
}

double& CMyMatrix::at(int x, int y)		// Um auf den richtigen Punkt zugreifen zu können in der Matrix
{
	return wert.at(x + dim.spalte * y);
}

double CMyMatrix::at(int x, int y) const	//Const Methode benötigt, da det() sonst Problem anzeigt, dass die typen nicht passen.
{
	return wert.at(x + dim.spalte * y);
}

void CMyMatrix::set(int x, int y, double wert)	//An einem Bestimmten Punkt in der Matrix wenn Wert nachträglich ändern.
{
	at(x, y) = wert;
}

CMyMatrix CMyMatrix::invers() const
{
	if (dim.zeile == 2 && dim.spalte == 2 && det() != 0.0)
	{
		CMyMatrix inv;
		inv.set_dim(2, 2);
		inv.set(0, 0, at(1, 1));
		inv.set(0, 1, -at(0, 1));
		inv.set(1, 0, -at(1, 0));
		inv.set(1, 1, at(0, 0));

		return ((1.0 / det()) * inv);
	}
	else
	{
		throw runtime_error("dimension passt nicht");
	}
}

double CMyMatrix::det() const	// Die Determinate berechnen. 
{
	return ((this->at(0, 0) * this->at(1, 1)) - (this->at(0, 1) * this->at(1, 0))); // a*d-c*b
}

CMyVektor operator*(const CMyMatrix& a, const CMyVektor& x)
{
	CMyVektor ergebnis(a.dim.zeile);
	
	for (int i = 0; i < a.dim.zeile; i++)
	{
		ergebnis.set_Value(i, x.mal(a.zeile_als_vector(i)));
	}

	return ergebnis;
}

CMyMatrix operator*(double zahl, const CMyMatrix& x)
{
	CMyMatrix ergebnis = x;

	for (int i = 0; i < x.dim.zeile; i++)
	{
		for (int j = 0; j < x.dim.spalte; j++)
		{
			ergebnis.at(i, j) *= zahl;
		}
	}

	return ergebnis;
}

CMyMatrix jacobi(CMyVektor& x, jacobif f)
{
	CMyMatrix ergebnis;
	ergebnis.set_dim(f(x).get_size(), x.get_size());

	double h = 0.0001;
	for (int j = 0; j < f(x).get_size(); j++)
	{
		vector<double*> zeiger = ergebnis.zeiger_aufzeile(j);

		for (int i = 0; i < x.get_size(); i++)
		{
			CMyVektor xh = x;
			xh[i] += h;

			*zeiger.at(i) = (f(xh)[j] - f(x)[j]) / h;
		}
	}

	return ergebnis;
}

void newton(const CMyVektor& x, jacobif f)
{
	if (x.get_size() != 2 || f(x).get_size() != 2)
	{
		return;
	}
	else
	{
		CMyVektor dx(2);
		CMyVektor b (2);
		b = x;

		CMyMatrix jacob;
		CMyMatrix jacob_inv;

		CMyVektor fx = f(x);

		for (int i = 0; i < 50 && fx.get_betrag() > 1e-5; i++)
		{
			jacob = jacobi(b, f);
			jacob_inv = jacob.invers();

			cout << "Schritt " << i << ":" << endl;
			cout << "\tx = " << b << endl;
			cout << "\tf(x) = " << fx << endl;
			/*cout << "\tf'(x) = " << endl << "\t" << jacob << endl;*/
			cout << "\tf'(x) = " << endl << "\t\t"
				 << "( " << jacob.at(0, 0) << "; " << jacob.at(1, 0) << endl
				 << "\t\t" << jacob.at(0, 1) << "; " << jacob.at(1, 1) << " )" << endl;
			//cout << "\t(f'(x))^(-1) = " << endl << "\t" << jacob_inv << endl;
			cout << "\t(f'(x))^(-1) = " << endl << "\t\t"
				<< "( " << jacob_inv.at(0, 0) << "; " << jacob_inv.at(1, 0) << "; " << endl
				<< "\t\t" << jacob_inv.at(0, 1) << "; " << jacob_inv.at(1, 1) << " )" << endl;
			dx = (jacob_inv * (-1.0 * fx));
			cout << "\tdx = " << dx << endl;
			cout << "\t||f(x)|| = " << fx.get_betrag() << endl << endl;

			b = b + dx;
			fx = f(b);

		}

		if (fx.get_betrag() < 1e-5)
		{
			cout << "Ende wegen ||f(x)|| <1e-5 bei" << endl;
		}
		else
		{
			cout << "Ende wegen 50 Schritte bei" << endl;
		}

		cout << "\tx = " << b << endl;
		cout << "\tf(x) = " << fx << endl;
		cout << "\t||f(x)|| = " << fx.get_betrag() << endl;
	}
}

CMyVektor CMyMatrix::zeile_als_vector(int zeile) const
{	
	CMyVektor ergebnis(dim.spalte);

	for (int i = 0; i < dim.spalte; i++)
	{
		ergebnis.set_Value(i, at(i, zeile));
	}

	return ergebnis;
}

vector<double*> CMyMatrix::zeiger_aufzeile(int zeile)
{
	vector<double*> zeiger;

	for (int i = 0; i < dim.spalte; i++)
	{
		zeiger.push_back(&at(i, zeile));
	}

	return zeiger;
}

std::ostream& operator<<(std::ostream& ausgabe, const CMyMatrix& x)
{
	cout << "( ";

	for (int i = 0; i < x.dim.zeile; i++)
	{
		for (int j = 0; j < x.dim.spalte; j++)
		{
			cout << x.at(j, i) << "; ";
		}
		if (i + 1 >= x.dim.zeile)
		{
			cout << " )";
		}
	}

	return ausgabe;
}