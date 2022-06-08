#include "CLotto.h"
#include <iostream>
#include "CZufall.h"
using namespace std;

void print(vector<int> ausgabe)
{
	for (unsigned int i = 0; i < ausgabe.size(); i++)
	{
		cout << ausgabe[i];
		cout << endl;
	}
	cout << endl;
}

void aufgabe1()
{
	CZufall zufall;
	vector<int> ausgabe;

	// 1a
	cout << "Aufgabe 1a" << endl;
	for (int i = 0; i < 5; i++)
	{
		zufall.initialisiere(1);
		print(zufall.test(3, 7, 10000));
	}

	// 1b
	cout << "Aufgabe 1b" << endl;
	for (int i = 0; i < 5; i++)
	{
		zufall.initialisiere(i);
		print(zufall.test(3, 7, 10000));
	}

	// 1c
	cout << "Aufgabe 1c" << endl;
	for (int i = 0; i < 5; i++)
	{
		zufall.initialisiere(time(NULL));
		print(zufall.test(3, 7, 10000));
	}

	// 1d
	cout << "Aufgabe 1d" << endl;
	for (int i = 0; i < 5; i++)
	{
		print(zufall.test_falsch(3,7,10000));
	}
}

void aufgabe3()
{
	//Aufgabe 3

	int r = 3;
	int k = 6;
	int n = 49;
	int N = 100000;

	int richtig = 0;

	CLotto s1(-1);
	s1.set_tippzettel({ 1,2,3,4,5,6 });
	for (int i = 0; i < N; i++)
	{
		if (s1.AnzahlTrefferTippzettel(k, n) == r)
		{
			richtig++;
		}
	}
	cout << "Wahrscheinlichkeit von " << r << " richtigen Zahlen mit festgelegtem Tippzettel: " << endl
		 << double(richtig) / N * 100 << "%" << endl << endl;


	CLotto s2(-1);
	richtig = 0;
	for (int i = 0; i < N; i++)
	{
		if (s2.Ziehung2(k, n) == r)
		{
			richtig++;
		}
	}
	cout << "Wahrscheinlichkeit von " << r << " richtigen Zahlen mit random Tippzettel: " << endl
		<< double(richtig) / N * 100 << "%" << endl << endl;

	CLotto s3(-1);
	s3.set_tippzettel({ 1,2,3,4,5,6 });
	cout << "Spieler 1 per Monte-Carlo Funktion" << endl
		 << s3.Monte_Carlo(r, k, n, N, true) << "%" << endl;

	CLotto s4(-1);
	cout << "Spieler 2 per Monte-Carlo Funktion" << endl
		 << s4.Monte_Carlo(r, k, n, N, false) << "%" << endl << endl;
}

void etest()
{
	// E-Test
	CLotto etest(-1);

	cout << "Aufgabe E-Test" << endl
		 << etest.Monte_Carlo(3, 6, 38, 100000, false) << "%" << endl;
}

int main()
{
	int eingabe = 0;
	while (eingabe != 4)
	{
		cout << endl;
		cout << " #########################" << endl
		 	 << " # Auswahl Menu by Ahmed #" << endl
			 << " #########################" << endl

			 << " 1. Fur Aufgabe 1" << endl
			 << " 2. Fur Aufgabe 3" << endl
			 << " 3. Fur E-Test" << endl
			 << " 4. Zum Abbrechen" << endl
			 << " -> ";
		cin >> eingabe;
		cout << endl;

		switch (eingabe)
		{
		case 1:
			aufgabe1();
			break;

		case 2:
			aufgabe3();
			break;

		case 3:
			etest();
			break;
		
		case 4:
			break;

		default:
			cout << "Eingabe war leider Ungultig!" << endl;
			break;
		}
	}

	system("PAUSE");
	return 0;
}