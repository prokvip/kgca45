#include "TVector.h"
float TVector2::length()// 크기
{
	return sqrt(x * x + y * y);
}
void  TVector2::Normalized() // 정규화
{
	float fInvert = 1.0f/length();
	x = x * fInvert;
	y = y * fInvert;
}
bool  TVector2::IsIdentity() // 단위벡터 판단
{
	float flength = length();
	return ((fabs(1.0f - flength) < T_EPSILON) ? true : false);
}
TVector2::TVector2() 
{
	x = 0.0f;
	y = 0.0f;
}
TVector2::TVector2::TVector2(float x, float y)
{
	v[0] = x;
	v[1] = y;
}
TVector2::TVector2(const TVector2& v)
{
	*this = v;
}
TVector2 TVector2::operator + (TVector2& v)
{
	return TVector2(x + v.x, y + v.y);
}
TVector2 TVector2::operator - (TVector2& v)
{
	return TVector2(x - v.x, y - v.y);
}
TVector2 TVector2::operator * (float s)
{
	return TVector2(x * s, y * s);
}
TVector2 TVector2::operator / (float s)
{
	return TVector2(x / s, y / s);
}
// a += b;
TVector2 TVector2::operator += (TVector2& v)
{	
	x += v.x;
	y += v.y;
	return *this;
}
TVector2 TVector2::operator -= (TVector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
TVector2 TVector2::operator *= (float s)
{
	x *= s;
	y *= s;
	return *this;
}
TVector2 TVector2::operator /= (float s)
{
	x /= s;
	y /= s;
	return *this;
}
bool TVector2::operator == (TVector2& v)
{
	// 0.99999 == 1.0f
	if (fabs(x-v.x) < T_EPSILON )
	{
		if (fabs(y - v.y) < T_EPSILON)
		{
			return true;
		}
	}
	return false;
}
bool TVector2::operator != (TVector2& v)
{
	return !(*this == v);
}
bool TVector2::operator < (TVector2& v)
{
	if (x < v.x)
	{
		if (y < v.y)
		{
			return true;
		}
	}
	return false;
}
bool TVector2::operator > (TVector2& v)
{
	return !(*this < v);
}

TVector4::TVector4()
{
	x = 0.0f;	y = 0.0f;	z = 0.0f;	w = 0.0f;
}
TVector4::TVector4(float x, float y, float z, float w)
{
	v[0] = x; v[1] = y; v[2] = z; v[3] = w;
}
TVector4::TVector4(const TVector4& v)
{
	*this = v;
}
TVector4 TVector4::operator + (TVector4& v)
{
	return TVector4(x + v.x, y + v.y, z+v.z, w+v.w);
}
TVector4 TVector4::operator - (TVector4& v)
{
	return TVector4(x - v.x, y - v.y, z-v.z, w-v.w);
}
TVector4 TVector4::operator * (float s)
{
	return TVector4(x * s, y * s, z*s, w*s);
}
TVector4 TVector4::operator / (float s)
{
	return TVector4(x / s, y / s, z/s, w/s);
}
// a += b;
TVector4 TVector4::operator += (TVector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}
TVector4 TVector4::operator -= (TVector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	z -= v.w;
	return *this;
}
TVector4 TVector4::operator *= (float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}
TVector4 TVector4::operator /= (float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}
bool TVector4::operator == (TVector4& v)
{
	// 0.99999 == 1.0f
	if (fabs(x - v.x) < T_EPSILON)
	{
		if (fabs(y - v.y) < T_EPSILON)
		{
			if (fabs(z - v.z) < T_EPSILON)
			{
				if (fabs(w - v.w) < T_EPSILON)
				{
					return true;
				}
			}
			return true;
		}
	}
	return false;
}
bool TVector4::operator != (TVector4& v)
{
	return !(*this == v);
}
bool TVector4::operator < (TVector4& v)
{
	if (x < v.x)
	{
		if (y < v.y)
		{
			if (z < v.z)
			{
				if (w < v.w)
				{
					return true;
				}
			}
			return true;
		}
	}
	return false;
}
bool TVector4::operator > (TVector4& v)
{
	return !(*this < v);
}
float TVector4::length()// 크기
{
	return sqrt(x * x + y * y + z*z+ w*w);
}
void  TVector4::Normalized() // 정규화
{
	float fInvert = 1.0f / length();
	x = x * fInvert;
	y = y * fInvert;
	z = z * fInvert;
	w = w * fInvert;
}
bool  TVector4::IsIdentity() // 단위벡터 판단
{
	float flength = length();
	return ((fabs(1.0f - flength) < T_EPSILON) ? true : false);
}