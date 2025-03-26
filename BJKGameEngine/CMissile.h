#pragma once
#include "CObject.h"
class CMissile : public CObject
{
public:
	CMissile();
	~CMissile();

public:
	virtual void update();
	virtual void render(HDC _dc);
public:
	float m_Theta; // 이동 방향
	FVector2D m_Dir;

	void SetTheta(float _Theta) { m_Theta = _Theta; }
	void SetDir(FVector2D _Dir) 
	{ 
		m_Dir = _Dir; 
		m_Dir.Normalize();
	}

};

