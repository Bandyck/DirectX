#pragma once

class cMatrix;
class cVector3
{
public:
	float x;
	float y;
	float z;
public:
	cVector3();
	~cVector3();
	cVector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {};
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

	bool operator==(cVector3 & vec);
	bool operator!=(cVector3 & vec);

	cVector3 operator+(cVector3 & vec);
	cVector3 operator-(cVector3 & vec);
	cVector3 operator*(float f);
	cVector3 operator/(float f);

	static float Dot(cVector3 & v1, cVector3 & v2);
	static cVector3 Cross(cVector3 & v1, cVector3 & v2);
	float Length();
	cVector3 Normalize();
	static float Angle(cVector3 & v1, cVector3 & v2);

	static cVector3 TransformCoord(cVector3 & v, cMatrix & mat);	// 점 이동
	static cVector3 TransformNormal(cVector3 & v, cMatrix & mat);	// 벡터 이동
};