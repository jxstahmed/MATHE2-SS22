#include "CMyVektor.h"
#include <vector>
#include <tuple>
#include <iostream>

struct Tuple
{
	int zeile;
	int spalte;
};

class CMyMatrix
{
private:
	std::vector<double> wert;
	Tuple dim = { 0, 0 };

public:
	CMyMatrix() = default;

	void set_dim(int x, int y);

	double& at(int x, int y);
	double at(int x, int y) const;
	void set(int x, int y, double wert);

	CMyMatrix invers() const;
	double det() const;


	friend CMyVektor operator*(const CMyMatrix& a, const CMyVektor& x);
	friend CMyMatrix operator*(double zahl, const CMyMatrix& x);
	friend std::ostream& operator<<(std::ostream& ausgabe, const CMyMatrix& x);

	CMyVektor spalte_als_vector(int spalte) const;
	CMyVektor zeile_als_vector(int zeile) const;
	std::vector<double*> zeiger_aufzeile(int zeile);
};

typedef CMyVektor(*jacobif)(const CMyVektor& x);
CMyMatrix jacobi(CMyVektor& x, jacobif f);
void newton(const CMyVektor& x, jacobif f);