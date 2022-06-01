#include "CKomplex.h"
#include <fstream>   
#include <vector>
#include <iomanip>

using namespace std;

#define PI 3.14159265358979323846264338327950288419

void print(const vector<CKomplex>& vals)
{
	for (int i = 0; i < vals.size(); i++)
	{
		if (i % 10 == 0 && i != 0)
		{
			cout << endl << endl;
		}
		cout << setw(10) << vals[i];
	}
	cout << endl;
}

vector<CKomplex>  werte_einlesen(const char *dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	if (!fp.is_open())
		cerr << "Datei " << dateiname << " konnte nicht geoeffnet werden...\n";
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i<N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const char *dateiname, vector<CKomplex> werte, double epsilon = -1.0)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	//fp.precision(10);
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}

vector<CKomplex> fourier_trafo(bool hin, vector<CKomplex> werte)
{
	unsigned int N = werte.size();
	vector<CKomplex> trafo;
	vector<CKomplex> temp;
	trafo.resize(N);
	temp.resize(N);

	CKomplex ephi{0,0};
	double phi = 0.0;

	for (int i = 0; i < N; i++)
	{
		temp[i] = CKomplex{ 0,0 };
		for (int x = 0; x < N; x++)
		{
			if (hin)
			{
				phi = (double(i) * double(x) * double(-2) * double(PI)) / double(N);
			}
			else
			{
				phi = (double(i) * double(x) * double(2) * double(PI)) / double(N);
			}

			ephi = CKomplex{ phi };
			temp[i] = temp[i] + (werte[x] * ephi);
		}
		trafo[i] = (1 / sqrt(N)) * temp[i];
	}

	return trafo;
}

double max_abweichung(vector<CKomplex>& vec1, vector<CKomplex>& vec2)
{
	double max = 0.0;
	if (vec1.size() == 0 || vec2.size() == 0)
	{
		cout << "Die Vectoren sind leer.\n";
		return -1;
	}
	else
	{
		for (int i = 0; i < vec1.size(); i++)
		{
			if (abs(vec1[i].re() - vec2[i].re()) > max)
			{
				max = abs(vec1[i].re() - vec2[i].re());
			}
		}
		return max;
	}
}

int main()
{
	
	vector<CKomplex> werte = werte_einlesen("Daten_original.txt");
	vector<CKomplex> hin_trafo = fourier_trafo(true, werte);

	werte_ausgeben("standard_eps_hin.txt", hin_trafo);
	werte_ausgeben("0.001_eps_hin.txt", hin_trafo, 0.001);
	werte_ausgeben("0.01_eps_hin.txt", hin_trafo, 0.01);
	werte_ausgeben("0.1_eps_hin.txt", hin_trafo, 0.1);
	werte_ausgeben("1.0_eps_hin.txt", hin_trafo, 1.0);

	hin_trafo = werte_einlesen("standard_eps_hin.txt");
	hin_trafo = fourier_trafo(false, hin_trafo);
	cout << "Maximale Abweichung bei Standard-Epsilon: " << max_abweichung(werte, hin_trafo) << endl;

	hin_trafo = werte_einlesen("0.001_eps_hin.txt");
	hin_trafo = fourier_trafo(false, hin_trafo);
	cout << "Maximale Abweichung bei epsilon=0.001: " << max_abweichung(werte, hin_trafo) << endl;

	hin_trafo = werte_einlesen("0.01_eps_hin.txt");
	hin_trafo = fourier_trafo(false, hin_trafo);
	cout << "Maximale Abweichung bei epsilon=0.01: " << max_abweichung(werte, hin_trafo) << endl;

	hin_trafo = werte_einlesen("0.1_eps_hin.txt");
	hin_trafo = fourier_trafo(false, hin_trafo);
	cout << "Maximale Abweichung bei epsilon=0.1: " << max_abweichung(werte, hin_trafo) << endl;

	hin_trafo = werte_einlesen("1.0_eps_hin.txt");
	hin_trafo = fourier_trafo(false, hin_trafo);
	cout << "Maximale Abweichung bei epsilon=1.0: " << max_abweichung(werte, hin_trafo) << endl;

	cout << endl;
	system("pause");
    return 0;
}