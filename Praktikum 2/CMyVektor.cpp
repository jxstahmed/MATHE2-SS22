#include "CMyVektor.h"
#include <string>
using namespace std;

static const double H(0.00000001);

CMyVektor::CMyVektor() // Nutzen der library assign Methode
{
    Vector.assign(1, 0.0);
}

CMyVektor::CMyVektor(int size, double wert) // Konstruktor um einen expliziten Vektor zu erstellen
{
    Vector.assign(size, wert);
}

CMyVektor::~CMyVektor() // Dekstruktor -> War nicht gefragt aber war jetzt kein Aufwand
{
    Vector.clear();
}

CMyVektor::CMyVektor(std::initializer_list<double>&& liste)
{
    Vector.resize(liste.size());
    Vector = liste;
}

void CMyVektor::set_Dimension(int Dimension) // Nachträglich die Dimension noch umändern
{
    Vector.resize(Dimension);
};

void CMyVektor::set_Value(int index, double wert) //Speziell nochmal den Wert an einer bestimmten Stelle im Vector ändern.
{
    Vector[index] = wert;
};

int CMyVektor::get_size() const// Sagt der Name ja schon was hier passiert.
{
    return Vector.size();
};

CMyVektor operator +(CMyVektor vec, CMyVektor vec2) // Operator für Vektor Addition.
{
    CMyVektor x(vec.get_size());
    if (vec.get_size() == vec2.get_size()) // Wenn die groeße passen, dann rechnet er. Sonst nicht, weil passt ja nicht.
    {
        for (int zaehler = 0; zaehler < vec.get_size(); zaehler++)
        {
            x[zaehler] = vec[zaehler] + vec2[zaehler];
        }
        return x;
    }
}

double CMyVektor::mal(const CMyVektor& vek) const
{
    if (vek.get_size() == get_size())
    {
        double ergebnis = 0.0;

        for (int i = 0; i < get_size(); i++)
        {
            ergebnis += vek[i] * (*this)[i];
        }
        return ergebnis;
    }
    else
    {
        throw runtime_error("Die Dimensionen der beiden Vektoren passen für Mul nicht!");
    }
}

CMyVektor operator *(double lambda, CMyVektor x) //Hier macht er Multiplikation
{
    CMyVektor y = x;
    int groeße = x.get_size();

    for (int i = 0; i < groeße; i++)
    {
        y[i] *= lambda;
    }
    return y;
}

double& CMyVektor::operator [](int index) //Überladungs Operator
{
    return Vector[index];
}

double CMyVektor::operator [](int index) const //Selbe wie oben, aber nur als const Methode für die funktionen.
{
    return Vector[index];
}

CMyVektor gradient(CMyVektor x, funktion f) // Gradienten Berechnung.
{
    int dim = x.get_size();

    CMyVektor ergebnis(dim);

    for (int i = 0; i < dim; i++)
    {
        CMyVektor xh = x; //Kopiert x in xh und dann rechnen wir an jeder Stell in xh dann * lambda.
        xh[i] += H;

        ergebnis[i] = (f(xh) - f(x)) / H; // Hier rechnen wir den endültigen Gradienten numerisch. || F(x) vorher ausrechnen besser.
    }
    return ergebnis;
}


void maximierung(CMyVektor x, funktion f, double lambda) // Hier geschieht die Maximierung.
{
    CMyVektor gradfx = gradient(x, f);
 

    for (int i = 0; i < 25 && gradfx.get_betrag() >= 1e-5; i++, gradfx = gradient(x, f)) // For schleife mit Abbruch ausreichende Schritte oder halt zu kleiner Betrag
    {
        CMyVektor xneu = x + (lambda * gradfx);
        cout << "Schritt " << i << ":" << endl
            << "\tx = " << x << endl
            << "\tlambda = " << lambda << endl
            << "\tf(x) = " << f(x) << endl
            << "\tgrad f(x) = " << gradfx << endl
            << "\t||grad f(x)|| = " << gradfx.get_betrag() << endl << endl
            << "\tx_neu = " << xneu << endl
            << "\tf(x_neu) = " << f(xneu) << endl << endl;

        if (f(xneu) > f(x)) //Wenn das neue x größer ist als das alte, testen wir doppelte. Damit wir schneller vorankommen.
        {
            CMyVektor xtest = x + (2 * (lambda * gradfx));

            cout << "\tTest mit doppelter Schrittweite (lambda = " << lambda * 2 << "):" << endl
                << "\tx_test = " << xtest << endl
                << "\tf(x_test) = " << f(xtest) << endl;

            if (f(xtest) > f(xneu)) // Falls der Test gut war, nehmen dir die doppelte Schritweite.
            {
                cout << "\tverdoppele Schrittweite!" << endl << endl;

                lambda *= 2.0;
                x = xtest;
            }
            else //Falls nicht, dann behalten wir die alte bei.
            {
                cout << "\tbehalte alte Schrittweite!" << endl << endl;
                x = xneu;
            }
        }
        else // War das neue x kleiner oder/gleich dem alten, halbieren wir die Schrittweite.
        {
            while (f(xneu) <= f(x)) // Aber nur solange, bis das neue x größer als das alte ist.
            {
                lambda /= 2.0;
                xneu = x + (lambda * gradfx);

                cout << "\thalbiere Schrittweite (lambda = " << lambda << "):" << endl
                << "\tx_neu = " << xneu << endl
                << "\tf(x_neu) = " << f(xneu) << endl << endl;
            }
            x = xneu;
        }
    }

    if (gradfx.get_betrag() < 1e-5) // Abbruch Bedingung 1. Wenn bestimmte Länge überschritten.
    {
        cout << "Ende wegen ||grad f(x)||<1e-5 bei " << endl;
    }
    else // Sonst halt ausreichend viele Schritte gemacht.
    {
        cout << "Ende wegen Schrittanzahl = 25 bei" << endl;
    }
    //Nochmal letzte Aussage
    cout << "\tx = " << x << endl
        << "\tlambda = " << lambda << endl
        << "\tf(x) = " << f(x) << endl
        << "\tgrad f(x) = " << gradfx << endl
        << "\t||grad f(x)|| = " << gradfx.get_betrag() << endl;
}

double CMyVektor::get_betrag() //Hier berechnen wir die Länge/Betrag
{
    double ergebnis(0.0);
    int groeße = get_size();
    for (int i = 0; i != groeße; i++)
    {
        ergebnis += ((*this)[i] * (*this)[i]);
    }
    return sqrt(ergebnis);
}



ostream& operator <<(ostream& stream, CMyVektor& myclass) //Musste Operator einrichten, damit wir die Vektoren ausgeben können
{
    stream << "( ";
    int groeße = myclass.get_size();

    for (int i = 0; i < groeße; i++)
    {
        stream << myclass[i];

        if (i + 1 < groeße)
        {
            stream << "; ";
        }
    }
    stream << ")";

    return stream;
}