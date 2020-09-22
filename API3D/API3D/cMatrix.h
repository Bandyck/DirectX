#pragma once
#include "cVector3.h"
#define EPSILON 0.0001f

class cMatrix
{
private:
	class cRow
	{
	private:
		std::vector<float> m_vecData;
	public:
		cRow();
		cRow(int nDimension);
		~cRow() {}
		void	Resize(int nDimension);
		float & operator[](int nIndex);
	};
	std::vector<cRow> m_vecData;
public:
	std::vector<cRow> cCol;
	cMatrix();
	~cMatrix();
	cMatrix(int nDimension);

	void	Print();
	void	Resize(int nDimension);
	int		Dimension();

	static	cMatrix Identity(int nDimension);

	cRow &	operator[](int nIndex);
	bool	operator==(cMatrix & mat);
	bool	operator!=(cMatrix & mat);
	cMatrix operator+(cMatrix & mat);
	cMatrix operator-(cMatrix & mat);
	cMatrix operator*(cMatrix & mat);
	cMatrix operator*(float f);

	float	Determinant();
	float	Cofactor(int nRow, int nCol);
	float	Minor(int nRow, int nCol);

	cMatrix Transpose();
	cMatrix Adjoint();
	cMatrix Inverse(OUT float& fDeterminant);

	static cMatrix Translation(float x, float y, float z);
	static cMatrix Translation(cVector3 & v);
	static cMatrix RotationX(float angle);
	static cMatrix RotationY(float angle);
	static cMatrix RotationZ(float angle);
	static cMatrix View(cVector3 & vEye, cVector3 & vLookAt, cVector3 & vUp);
	static cMatrix Projection(float fFovY, float fAspect, float fNearZ, float fFarZ);
	static cMatrix Viewport(float x, float y, float w, float h, float minz, float maxz);
};
///*
//	View Matrix
//		eye, look at, up
//		l = look vector
//		r = right vector
//		u = up vector
//			
//			r.x			u.x			l.x			0
//			r.y			u.y			l.y			0
//			r.z			u.z			l.z			0
//			-r dot eye	-u dot eye	-l dot eye	0
//*/
///*
//	Projection Matrix
//		sy = cot(fovy/2)		=> 1.0f / tanf(fFovY/2.0f)
//		sx = sy / aspect
//
//			sx		0		0					0
//			0		sy		0					0
//			0		0		fz/(fz-nz)			1
//			0		0		-fz*nz / (fz-nz)	0
//*/
///*
//	Viewport Matrix
//		Usually, maxz = 1, minz = 0
//
//			w/2.0f		0			0			0
//			0			-h/2.0f		0			0
//			0			0			maxz-minz	0
//			x+w/2.0f	y+h/2.0f	minz		1
//*/
///*
//	S*R*T*V*P*Vp
//*/
//#pragma once
//#include "stdafx.h"
//class cMatrix
//{
//
//public:
//	cMatrix operator/(float f);
//	cMatrix Minor(int nRow, int nCol);
//	cMatrix Getmat();
//
//};