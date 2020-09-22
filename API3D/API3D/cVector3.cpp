#include "cVector3.h"
#include "stdafx.h"
#define EPSILON	0.0001f

cVector3::cVector3() : x(0.0f), y(0.0f), z(0.0f){}
cVector3::~cVector3(){}
bool cVector3::operator==(cVector3 & vec)
{
	if (x - EPSILON <= vec.x && vec.x <= x + EPSILON &&	
		y - EPSILON <= vec.y && vec.y <= y + EPSILON &&	
		z - EPSILON <= vec.z && vec.z <= z + EPSILON)
	{	return true;	}
	return false;
}
bool cVector3::operator!=(cVector3 & vec)
{
	return !(*this == vec);
}
cVector3 cVector3::operator+(cVector3 & vec)
{
	return cVector3(x + vec.getX(), y + vec.getY(), z + vec.getZ());
}
cVector3 cVector3::operator-(cVector3 & vec)
{
	return cVector3(x - vec.getX(), y - vec.getY(), z - vec.getZ());
}

cVector3 cVector3::operator*(float f)
{
	return cVector3(x * f, y * f, z * f);
}
cVector3 cVector3::operator/(float f)
{
	return cVector3(x / f, y / f, z / f);
}
float cVector3::Dot(cVector3 & v1, cVector3 & v2)
{
	return v1.getX()*v2.getX() + v1.getY()*v2.getY() + v1.getZ()*v2.getZ();
}
cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)
{
	return cVector3(
		v1.getY() * v2.getZ() - v1.getZ() * v2.getY(),
		v1.getZ() * v2.getX() - v1.getX() * v2.getZ(),
		v1.getX() * v2.getY() - v1.getY() * v2.getX()
	);
}
float cVector3::Length()
{
	return sqrt(x*x + y*y + z*z);
}
cVector3 cVector3::Normalize()
{
	return cVector3(x / Length(), y / Length(), z / Length());
}
float cVector3::Angle(cVector3 & v1, cVector3 & v2) 
{
	return acos(Dot(v1, v2) / (v1.Length()*v2.Length()));
}
//cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix & mat)
//{
//	cMatrix matret = cMatrix::Identity(4);
//
//	matret[0][0] = v.getX();
//	matret[1][1] = v.getY();
//	matret[2][2] = v.getZ();
//	
//	matret = matret * mat;
//
//	cVector3 vecret(matret[0][0], matret[1][1], matret[2][2]);
//	return vecret;
//}
cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix & mat)
{
	cVector3 vRet = v;
	float w = 1;
	vRet.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0] + 1 * mat[3][0];
	vRet.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1] + 1 * mat[3][1];
	vRet.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2] + 1 * mat[3][2];
	w = v.x * mat[0][3] + v.y * mat[1][3] + v.z * mat[2][3] + 1 * mat[3][3];
	vRet.x /= w;
	vRet.y /= w;
	vRet.z /= w;
	return vRet;
}
//cVector3 cVector3::TransformNormal(cVector3 & v, cMatrix & mat)
//{
//	cMatrix matret = cMatrix::Identity(4);
//
//	matret[0][0] = v.getX();
//	matret[1][1] = v.getY();
//	matret[2][2] = v.getZ();
//	matret[3][3] = 0;
//
//	matret = matret * mat;
//
//	cVector3 vecret(matret[0][0], matret[1][1], matret[2][2]);
//	return vecret;
//}
cVector3 cVector3::TransformNormal(cVector3 & v, cMatrix & mat)
{
	cVector3 vRet;

	vRet.x = v.x *mat[0][0] + v.y*mat[1][0] + v.z * mat[2][0];
	vRet.y = v.x *mat[0][1] + v.y*mat[1][1] + v.z * mat[2][1];
	vRet.z = v.x *mat[0][2] + v.y*mat[1][2] + v.z * mat[2][2];

	return vRet;
}


//float cVector3::Angle(cVector3 & v1, cVector3 & v2)
//{
//	float angle = acosf(cVector3::Dot(v1, v2) / (v1.Length()*v2.Length())) * (180 / PI);
//
//	return angle;
//}
//cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix & mat)
//{
//	cVector3 Moved = v;
//	float w = 1;
//	Moved.x = v.x * mat[0][0] + v.y * mat[1][0] + v.z * mat[2][0] + 1 * mat[3][0];
//	Moved.y = v.x * mat[0][1] + v.y * mat[1][1] + v.z * mat[2][1] + 1 * mat[3][1];
//	Moved.z = v.x * mat[0][2] + v.y * mat[1][2] + v.z * mat[2][2] + 1 * mat[3][2];
//	w = v.x * mat[0][3] + v.y * mat[1][3] + v.z * mat[2][3] + 1 * mat[3][3];
//
//	Moved.x = Moved.x / w;
//	Moved.y = Moved.y / w;
//	Moved.z = Moved.z / w;
//
//	return Moved;
//}
//
//cVector3 cVector3::TransformNormal(cVector3 & v, cMatrix & mat)
//{
//	cVector3 Moved = v;
//	Moved.x = v.x * mat[0][0] + v.y * mat[0][1] + v.z * mat[0][2];
//	Moved.y = v.x * mat[1][0] + v.y * mat[1][1] + v.z * mat[1][2];
//	Moved.z = v.x * mat[2][0] + v.y * mat[2][1] + v.z * mat[2][2];
//
//	return Moved;
//}