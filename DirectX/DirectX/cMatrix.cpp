#include "stdafx.h"
#include "cMatrix.h"
#include "cVector3.h"
// >> cRow
cMatrix::cRow::cRow()	{}
cMatrix::cRow::cRow(int nDimension)
{
	m_vecData.resize(nDimension);
}
void cMatrix::cRow::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
}
float & cMatrix::cRow::operator[](int nIndex)
{
	return m_vecData[nIndex];
}
// >> cMatrix
cMatrix::cMatrix() {}
cMatrix::~cMatrix() {}
cMatrix::cMatrix(int nDimension)
{
	Resize(nDimension);
}
void cMatrix::Print()
{
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j < Dimension(); j++)
		{
			printf("%8.2f", (*this)[i][j]);
		}
		cout << endl;
	}	
}
void cMatrix::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
	for (size_t i = 0; i < nDimension; i++)
		m_vecData[i].Resize(nDimension);
}
int	cMatrix::Dimension()
{
	return (int)m_vecData.size();
}
cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix matret(nDimension);

	for (int i = 0; i < nDimension; i++)
		for (int j = 0; j < nDimension; j++)
			matret[i][j] = (i == j) ? 1 : 0;

	return matret;
}
cMatrix::cRow & cMatrix::operator[](int nIndex)
{
	return m_vecData[nIndex];
}
bool cMatrix::operator==(cMatrix & mat)
{
	for(int i=0;i<Dimension();i++)
		for (int j = 0; j < Dimension(); j++)
		{
			if ((*this)[i][j] - EPSILON > mat[i][j])
				return false;
			if ((*this)[i][j] - EPSILON < mat[i][j])
				return false;
		}
	return true;
}
bool cMatrix::operator!=(cMatrix & mat)
{
	return !((*this) == mat);
}
cMatrix cMatrix::operator+(cMatrix & mat)
{
	cMatrix matret(Dimension());

	for (int i = 0; i < Dimension(); i++)
		for (int j = 0; j < Dimension(); j++)
			matret[i][j] = (*this)[i][j] + mat[i][j];
	
	return matret;
}
cMatrix cMatrix::operator-(cMatrix & mat)
{
	cMatrix matret(Dimension());

	for (int i = 0; i < Dimension(); i++)
		for (int j = 0; j < Dimension(); j++)
			matret[i][j] = (*this)[i][j] - mat[i][j];

	return matret;
}
cMatrix cMatrix::operator*(cMatrix & mat)
{
	cMatrix matret(Dimension());

	for(int i=0;i<Dimension();i++)
		for (int j = 0; j < Dimension(); j++)
		{
			matret[i][j] = 0.0f;
			for (int k = 0; k < Dimension(); k++)
			{
				matret[i][j] = matret[i][j] + (*this)[i][k] * mat[k][j];
			}
		}

	return matret;
}
cMatrix cMatrix::operator*(float f)
{
	cMatrix matret(Dimension());

	for (int i = 0; i < Dimension(); i++)
		for (int j = 0; j < Dimension(); j++)
			matret[i][j] = (*this)[i][j] * f;

	return matret;
}
float cMatrix::Determinant()
{
	if (Dimension() == 1)
		return (*this)[0][0];
	if (Dimension() == 2)
		return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];

	float fDeterminant = 0.0f;
	for (int i = 0; i < Dimension(); i++)
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));

	return fDeterminant;
}
float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;
	if ((nRow + nCol) % 2 != 0)
		nConst = -1;

	return nConst * Minor(nRow, nCol);
}
float cMatrix::Minor(int nRow, int nCol)
{
	cMatrix MinorMat(Dimension() - 1);
	int MinorRow = 0;
	int MinorCol = 0;

	for (int i = 0; i < Dimension(); i++)
	{
		if (nRow == i)
			continue;
		for (int j = 0; j < Dimension(); j++)
		{
			if (nCol == j)
				continue;
			MinorMat[MinorRow][MinorCol] = (*this)[i][j];
			++MinorCol;
		}
		++MinorRow;
	}
	return MinorMat.Determinant();
}

cMatrix cMatrix::Transpose()
{
	cMatrix matret(Dimension());
	
	for (int i = 0; i < Dimension(); i++)
		for (int j = 0; j < Dimension(); j++)
			matret[i][j] = (*this)[j][i];

	return matret;
}
cMatrix cMatrix::Adjoint()
{
	cMatrix matret(Dimension());

	for (int i = 0; i < Dimension(); i++)
		for (int j = 0; j < Dimension(); j++)
			matret[i][j] = Cofactor(j, i);

	return matret;
}
cMatrix cMatrix::Inverse(OUT float& fDeterminant)
{
	cMatrix matret = cMatrix::Identity(Dimension());
	fDeterminant = Determinant();
	if (-EPSILON < fDeterminant && fDeterminant < EPSILON)
	{
		cout << "Not exists Inverse Matrix" << endl;
		return matret;
	}

	cMatrix matadj = Adjoint();
	matret = matadj * (1 / fDeterminant);

	return matret;
}
cMatrix cMatrix::Translation(float x, float y, float z)
{
	cMatrix matret = cMatrix::Identity(4);
	matret[3][0] = x;
	matret[3][1] = y;
	matret[3][2] = z;

	return matret;
}
cMatrix cMatrix::Translation(cVector3 & v)
{
	cMatrix matret = cMatrix::Identity(4);
	matret[3][0] = v.getX();
	matret[3][1] = v.getY();
	matret[3][2] = v.getZ();

	return matret;
}
cMatrix cMatrix::RotationX(float angle)
{
	cMatrix matret = cMatrix::Identity(4);
	matret[1][1] = cos(angle);
	matret[1][2] = sin(angle);
	matret[2][1] = -sin(angle);
	matret[2][2] = cos(angle);

	return matret;
}
cMatrix cMatrix::RotationY(float angle)
{
	cMatrix matret = cMatrix::Identity(4);
	matret[0][0] = cos(angle);
	matret[0][2] = -sin(angle);
	matret[2][0] = sin(angle);
	matret[2][2] = cos(angle);

	return matret;
}
cMatrix cMatrix::RotationZ(float angle)
{
	cMatrix matret = cMatrix::Identity(4);
	matret[0][0] = cos(angle);
	matret[0][1] = sin(angle);
	matret[1][0] = -sin(angle);
	matret[1][1] = cos(angle);

	return matret;
}
cMatrix cMatrix::View(cVector3 & vEye, cVector3 & vLookAt, cVector3 & vUp)
{
	cVector3 l = (vLookAt - vEye).Normalize();
	cVector3 r = (cVector3::Cross(vUp, l).Normalize());
	cVector3 u = cVector3::Cross(l, r);

	cMatrix matret(4);
	
	matret[0][0] = r.getX();				matret[0][1] = u.getX();				matret[0][2] = l.getX();				matret[0][3] = 0;
	matret[1][0] = r.getY();				matret[1][1] = u.getY();				matret[1][2] = l.getY();				matret[1][3] = 0;
	matret[2][0] = r.getZ();				matret[2][1] = u.getZ();				matret[2][2] = l.getZ();				matret[2][3] = 0;
	matret[3][0] = -cVector3::Dot(r, vEye);	matret[3][1] = -cVector3::Dot(u, vEye);	matret[3][2] = -cVector3::Dot(l, vEye);	matret[3][3] = 0;

	return matret;
}
cMatrix cMatrix::Projection(float fFovY, float fAspect, float fNearZ, float fFarZ)
{
	float sy = 1.0f / tanf(fFovY / 2.0f);
	float sx = sy / fAspect;

	cMatrix matret(4);

	matret[0][0] = sx;	matret[0][1] = 0;	matret[0][2] = 0;									matret[0][3] = 0;
	matret[1][0] = 0;	matret[1][1] = sy;	matret[1][2] = 0;									matret[1][3] = 0;
	matret[2][0] = 0;	matret[2][1] = 0;	matret[2][2] = fFarZ / (fFarZ - fNearZ);			matret[2][3] = 1;
	matret[3][0] = 0;	matret[3][1] = 0;	matret[3][2] = -fFarZ*fNearZ / (fFarZ - fNearZ);	matret[3][3] = 0;

	return matret;
}
cMatrix cMatrix::Viewport(float x, float y, float w, float h, float minz, float maxz)
{

	cMatrix matret(4);

	matret[0][0] = w / 2.0f;		matret[0][1] = 0;				matret[0][2] = 0;			matret[0][3] = 0;
	matret[1][0] = 0;				matret[1][1] = -h / 2.0f;		matret[1][2] = 0;			matret[1][3] = 0;
	matret[2][0] = 0;				matret[2][1] = 0;				matret[2][2] = maxz - minz;	matret[2][3] = 0;
	matret[3][0] = x + w / 2.0f;	matret[3][1] = y + h / 2.0f;	matret[3][2] = minz;		matret[3][3] = 1;

	return matret;
}
/*
	View Matrix
		eye, look at, up
		l = look vector
		r = right vector
		u = up vector
			
			r.x			u.x			l.x			0
			r.y			u.y			l.y			0
			r.z			u.z			l.z			0
			-r dot eye	-u dot eye	-l dot eye	0
*/
/*
	Projection Matrix
		sy = cot(fovy/2)		=> 1.0f / tanf(fFovY/2.0f)
		sx = sy / aspect

			sx		0		0					0
			0		sy		0					0
			0		0		fz/(fz-nz)			1
			0		0		-fz*nz / (fz-nz)	0
*/
/*
	Viewport Matrix
		Usually, maxz = 1, minz = 0

			w/2.0f		0			0			0
			0			-h/2.0f		0			0
			0			0			maxz-minz	0
			x+w/2.0f	y+h/2.0f	minz		1
*/
/*
	S*R*T*V*P*Vp
*/