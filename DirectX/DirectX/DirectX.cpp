#include "stdafx.h"
#include "cVector3.h"
#include "cMatrix.h"

int main()
{
	//cVector3 A(0, 0, 0);
	//cVector3 B(0, 1, 3);
	//cVector3 C(5, 1, 0);

	//cVector3 v = cVector3::Cross(B, C);

	//cout << cVector3::Angle(B, v) * (180.0 / M_PI) << endl;
	//cout << cVector3::Angle(C, v) * (180.0 / M_PI) << endl;

	//cVector3 ab = A - B;
	//cVector3 ca = C - A;

	cMatrix mat = cMatrix::Identity(4);
	//
	//mat.Print();
	//cout << endl;
	//mat.Translation(1, 2, -3).Print();
	//cout << endl;
	//cVector3 A(1, 2, -3);
	//mat.Translation(A).Print();
	//cout << endl;
	//mat.RotationX(M_PI / 4).Print();
	//cout << endl;
	//mat.RotationY(M_PI / 4).Print();
	//cout << endl;
	//mat.RotationZ(M_PI / 4).Print();
	//cout << endl;
	//cVector3 vEye(0, 5, -5);
	//cVector3 vLookAt(0, 0, 0);
	//cVector3 vUp(0, 1, 0);
	//mat.View(vEye, vLookAt, vUp).Print();
	//cout << endl;
	//mat.Projection.Print();
	//mat.Viewport.Print();

	cVector3 p(5, 0, 0);
	cVector3 v = p.TransformCoord(p, mat.Translation(1, 2, -3));
	cout << v.getX() << ' ' << v.getY() << ' ' << v.getZ() << ' ' << endl;
    return 0;
}