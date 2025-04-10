#pragma once


struct CallBack
{
	void* instacne;			// 인스턴스 주소
	void (*func)(void*);	// 호출 함수
};

struct FVector2D
{
	float x;
	float y;



public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
		{
			return true;
		}
		return false;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	FVector2D& Normalize()
	{
		float Len = Length();

		assert(Len != 0.f);

		x /= Len;
		y /= Len;

		return *this;
	}
public:
	FVector2D& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}
	FVector2D operator + (FVector2D _other)
	{
		return FVector2D(x + _other.x, y + _other.y);
	}
	void operator += (FVector2D _other)
	{
		x += _other.x;
		y += _other.y;
	}
	FVector2D operator - (FVector2D _other)
	{
		return FVector2D(x - _other.x, y - _other.y);
	}
	FVector2D operator * (FVector2D _other)
	{
		return FVector2D(x * _other.x, y * _other.y);
	}

	FVector2D operator * (float _float)
	{
		return FVector2D(x * _float, y * _float);
	}

	FVector2D operator / (FVector2D _other)
	{
		assert(!(0.f == _other.x || 0.f == _other.y));
		return FVector2D(x / _other.x, y / _other.y);
	}
	FVector2D operator / (float _f)
	{
		assert(!(0.f == _f));
		return FVector2D(x / _f, y / _f);
	}



public:
	FVector2D()
		: x(0.f)
		, y(0.f)
	{
	}
	FVector2D(UINT _x, UINT _y)
		: x((float)_x)
		, y((float)_y)
	{
	}

	FVector2D(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	FVector2D(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{
	}

	FVector2D(long _x, long _y)
		: x((float)_x)
		, y((float)_y)
	{
	}

	FVector2D(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{
	}
};