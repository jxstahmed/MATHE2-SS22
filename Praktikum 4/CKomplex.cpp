#include "CKomplex.h"

CKomplex::CKomplex(double realteil, double imagteil)
{
    real = realteil;
    imag = imagteil;
}

CKomplex::CKomplex(double phi)
{
    real = cos(phi);
    imag = sin(phi);
}

double CKomplex::re() const
{
    return real;
}

double CKomplex::im() const
{
    return imag;
}

double CKomplex::abs() const
{
    return (sqrt(pow(real, 2) + pow(imag, 2)));
}

CKomplex operator+(const CKomplex& a, const CKomplex& b)
{
    CKomplex ergebnis{a.real, a.imag};

    ergebnis.imag += b.imag;
    ergebnis.real += b.real;

    return ergebnis;
}

CKomplex operator*(const CKomplex& a, const CKomplex& b)
{
    CKomplex ergebnis{0, 0};

    ergebnis.real = (a.real * b.real - b.imag * a.imag); // imag * imag = real wegen j * j
    ergebnis.imag = (a.real * b.imag + a.imag * b.real);

    return ergebnis;
}

CKomplex operator*(const double& a, const CKomplex& b)
{
	CKomplex ergebnis{ b.real, b.imag };

    ergebnis.real = a * b.real;
    ergebnis.imag = a * b.imag;

	return ergebnis;
}

std::ostream& operator<<(std::ostream& os, const CKomplex& c)
{
    os << c.re() << ((c.im() >= 0) ? " + " : "") << c.im() << "j";
    return os;
}