#pragma once
#include <math.h>
#define T_EPSILON 0.0001f

#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;
#define lerp(t,x,y)  (x+(t*(y - x)));

struct float2
{
	union {
		struct { float x; float y; };
		float v[2];
	};
};
struct float4
{
	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};
};
class TVector2 : public float2
{
public:
	TVector2();
	TVector2(float x, float y);
	TVector2(const TVector2& v);
public:
	TVector2 operator + (TVector2& v);
	TVector2 operator - (TVector2& v);
	TVector2 operator * (float s);
	TVector2 operator / (float s);
	TVector2 operator += (TVector2& v);
	TVector2 operator -= (TVector2& v);
	TVector2 operator *= (float s);
	TVector2 operator /= (float s);
	bool operator == (TVector2& v);
	bool operator != (TVector2& v);
	bool operator < (TVector2& v);
	bool operator > (TVector2& v);

	float length();		// 크기
	void  Normalized(); // 정규화
	bool  IsIdentity();
};
class TVector4 : public float4
{
public:
	TVector4();
	TVector4(float x, float y, float z, float w);
	TVector4(const TVector4& v);
	TVector4 operator + (TVector4& v);
	TVector4 operator - (TVector4& v);
	TVector4 operator * (float s);
	TVector4 operator / (float s);
	TVector4 operator += (TVector4& v);
	TVector4 operator -= (TVector4& v);
	TVector4 operator *= (float s);
	TVector4 operator /= (float s);
	bool operator == (TVector4& v);
	bool operator != (TVector4& v);
	bool operator < (TVector4& v);
	bool operator > (TVector4& v);
	float length();		// 크기
	void  Normalized(); // 정규화
	bool  IsIdentity();
};

