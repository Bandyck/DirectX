#include "cVector3.h"
#include "cMatrix.h"
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
cVector3 cVector3::TransformCoord(cVector3 & v, cMatrix & mat)
{
	cVector3 vecret;
	vecret.x = v.getX() + mat[3][0];
	vecret.y = v.getY() + mat[3][1];
	vecret.z = v.getZ() + mat[3][2];

	return vecret;
}
cVector3 cVector3::TransformNormal(cVector3 & v, cMatrix & mat)
{
	cVector3 vecret;
	vecret.x = v.getX();
	vecret.y = v.getY();
	vecret.z = v.getZ();

	return vecret;
}