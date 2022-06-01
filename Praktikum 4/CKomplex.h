#include <iostream>
#include <math.h>

class CKomplex
{

private:
    double real;
    double imag;

public:
	CKomplex() {};
	CKomplex(double realteil, double imagteil);
    CKomplex(double phi);

	double re() const;
    double im() const;
    double abs() const;

    friend std::ostream& operator<<(std::ostream & os, const CKomplex& c);
    friend CKomplex operator+(const CKomplex& a, const CKomplex& b);
    friend CKomplex operator*(const CKomplex& a, const CKomplex& b);
	friend CKomplex operator*(const double& a, const CKomplex& b);
};