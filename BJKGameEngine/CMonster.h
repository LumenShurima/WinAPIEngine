#pragma once
#include "CObject.h"
class CMonster : public CObject
{
public:
	CMonster();
	~CMonster();

private:
	FVector2D m_CenterPos;
	float m_Speed;
	float m_Range;
	int m_Dir;
	

public:
	float GetSpeed() { return m_Speed; }
	void SetSpeed(float _f) { m_Speed = _f; }

	void SetCenterPos(FVector2D _Pos) { m_CenterPos = _Pos; }
	void SetMoveDistance(float _Range) { m_Range = _Range; }
public:
	virtual void update();


	
};

