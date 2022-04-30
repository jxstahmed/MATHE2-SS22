#include "CMyMatrix.h"
#include "CMyVektor.h"
#include <iostream>

using namespace std;

CMyVektor f(const CMyVektor& x)
{
    return CMyVektor{pow(x[0], 3) * pow(x[1], 3) - 2 * x[1], x[0] - 2};
}

int main()
{
    newton(CMyVektor{ 1, 1 }, f);

    cout << endl;
    system("PAUSE");
    return 0;
}