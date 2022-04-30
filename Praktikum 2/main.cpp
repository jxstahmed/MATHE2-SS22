#include "CMyMatrix.h"
#include "CMyVektor.h"
#include <iostream>

using namespace std;


CMyVektor f2(const CMyVektor& x)
{
    return CMyVektor{
        x[0] * x[1] * exp(x[2]),
        x[1] * x[2] * x[3],
        x[3]
    };


}

CMyVektor f3(const CMyVektor& x)
{
    return CMyVektor{
        std::pow(x[0], 3) * std::pow(x[1], 3) - 2 * x[1],
        x[0] - 2
    };
}

int main()
{

    newton(CMyVektor{ 1, 1 }, f3);

    cout << endl;
    system("PAUSE");
    return 0;
}