#include "pch.h"
#include "CMonster.h"
#include "CTimeManager.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_CenterPos(FVector2D(0.f, 0.f))
	, m_Speed{100.f}
	, m_Range(50.f)
	, m_Dir(1)
	, m_HP(10)
{

	CreateCollider();

	GetCollider()->SetOffsetPos(FVector2D(0.f, 0.f));
	GetCollider()->SetScale(FVector2D(40.f, 40.f));
}

CMonster::~CMonster()
{

}



void CMonster::update()
{
	return;
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


void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* Owner = _pOther->GetOwner();

	if (Owner->GetName() == L"Missile_Player")
	{
		m_HP -= 1;

		if (m_HP <= 0)
		{
			DeleteObject(this);
		}
	}
}