#pragma once
#include <vector>
#include <iostream>

class CMyVektor
{

    friend std::ostream& operator << (std::ostream& stream, CMyVektor& cmv);
    friend CMyVektor operator +(CMyVektor vec, CMyVektor vec2);
    friend CMyVektor operator *(double lambda, CMyVektor x);

private:

    std::vector<double> Vector;

public:
    CMyVektor();
    CMyVektor(int size, double wert = 0.0);
    ~CMyVektor();
    CMyVektor(std::initializer_list<double>&& liste);

    void set_Dimension(int Dimension);
    void set_Value(int index, double wert);
    int get_size() const;
    double& operator [](int index);
    double operator [](int index) const;

    double get_betrag();

    double mal(const CMyVektor& vek) const;
};

typedef double (*funktion)(const CMyVektor& x); //Definition erstellt, um das ganze zuvereinfachen und abzukürzen.
void maximierung(CMyVektor x, funktion f, double lambda = 1.0);

CMyVektor gradient(CMyVektor x, funktion f);