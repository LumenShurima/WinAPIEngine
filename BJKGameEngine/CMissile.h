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
	float m_Theta; // �̵� ����
	void SetTheta(float _Theta) { m_Theta = _Theta; }

};

