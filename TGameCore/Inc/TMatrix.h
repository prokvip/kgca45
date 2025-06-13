#pragma once	
#include <math.h>

struct float3x3
{
	union {
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		float m[3][3];
	};
};
class TMatrix : public float3x3
{
public:
	TMatrix() {
		SetIdentity();
	}
	void SetIdentity() {
		_11 = 1.0f; _12 = 0.0f; _13 = 0.0f;
		_21 = 0.0f; _22 = 1.0f; _23 = 0.0f;
		_31 = 0.0f; _32 = 0.0f; _33 = 1.0f;
	}
	TMatrix(const TMatrix& matrix)
	{
		_11 = matrix._11; _12 = matrix._12; _13 = matrix._13;
		_21 = matrix._21; _22 = matrix._22; _23 = matrix._23;
		_31 = matrix._31; _32 = matrix._32; _33 = matrix._33;
	}
	TMatrix operator*(const TMatrix& matrix) 
	{
		TMatrix result;
		for (int iColumn = 0; iColumn < 3; iColumn++)
		{
			for (int iRow = 0; iRow < 3; iRow++)
			{
				result.m[iRow][iColumn] = 
					m[iRow][0] * matrix.m[0][iColumn] +
					m[iRow][1] * matrix.m[1][iColumn] +
					m[iRow][2] * matrix.m[2][iColumn];
			}
		}
		return result;
	}
	void Translaton(float x, float y)
	{
		_31 = x;
		_32 = y;
	}
	void Scale(float x, float y)
	{
		_11 = x;
		_22 = y;
	}
	void Rotation(float radian)
	{
		float cosValue = cosf(radian);
		float sinValue = sinf(radian);
		_11 = cosValue; _12 = sinValue; 
		_21 = -sinValue;_22 = cosValue;
	}
};