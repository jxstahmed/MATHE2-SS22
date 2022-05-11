#include "CMyVektor.h"

class C_DGLSolver
{
	typedef CMyVektor (*DGLSystem)(CMyVektor& y, double x);
	typedef double (*DGLSystemN)(CMyVektor& y, double x);

private:

	bool mn;

	union
	{
		DGLSystem erster;
		DGLSystemN n;
	}art;

public:

	C_DGLSolver(DGLSystem DGL_System);
	C_DGLSolver(DGLSystemN DGL_SystemN);

	CMyVektor ableitungen(CMyVektor& y, double x);
	CMyVektor euler(double x_start, double x_end, double schritt, const CMyVektor& y_start, std::ostream& ausgabe);
	CMyVektor heun(double x_start, double x_end, double schritt, const CMyVektor& y_start, std::ostream& ausgabe);
};