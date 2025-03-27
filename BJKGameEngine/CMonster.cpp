#include "pch.h"
#include "CMonster.h"
#include "CTimeManager.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_CenterPos(FVector2D(0.f, 0.f))
	, m_Speed{100.f}
	, m_Range(50.f)
	, m_Dir(1)
{

	CreateCollider();

	GetCollider()->SetOffsetPos(FVector2D(0.f, 0.f));
	GetCollider()->SetScale(FVector2D(50.f, 50.f));
}

CMonster::~CMonster()
{

}

void CMonster::update()
{
	FVector2D CurPos = GetPos();

	// 진행 방향으로 신당 Speed 만큼 이동
	CurPos.x += DeltaTime * m_Speed * m_Dir;
	
	
	float Dist = abs(m_CenterPos.x - CurPos.x) - m_Range;
	if (0.f < Dist)
	{
		m_Dir *= -1;
		CurPos.x += Dist * m_Dir;
	}

	SetPos(CurPos);
}
