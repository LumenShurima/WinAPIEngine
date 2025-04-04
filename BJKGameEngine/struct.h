#pragma once


struct FVector2D
{
	float x;
	float y;



public:
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
	FVector2D operator - (FVector2D _other)
	{
		return FVector2D(x - _other.x, y - _other.y);
	}
	FVector2D operator * (FVector2D _other)
	{
		return FVector2D(x * _other.x, y * _other.y);
	}
	FVector2D operator / (FVector2D _other)
	{
		assert(!(0.f == _other.x || 0.f == _other.y));
		return FVector2D(x / _other.x, y / _other.y);
	}

public:
	FVector2D()
		: x(0.f)
		, y(0.f)
	{}

	FVector2D(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	FVector2D(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	FVector2D(long _x, long _y)
		: x((float)_x)
		, y((float)_y)
	{}

	FVector2D(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
};