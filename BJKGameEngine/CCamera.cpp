#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CKeyManager.h"
#include "CTimeManager.h"

CCamera::CCamera()
	: m_pTargetObject(nullptr)
	, m_Time(0.7f)
	, m_Speed(0.f)
	, m_AccTime(0.7f)
{

}


CCamera::~CCamera()
{

}


void CCamera::update()
{
	if (m_pTargetObject)
	{
		if (m_pTargetObject->IsKilled())
		{
			m_pTargetObject = nullptr;
		}
		else
		{
			m_LookAt = m_pTargetObject->GetPos();
		}

	}

	if (KEY_Triggered(EKEY::UP))
		m_LookAt.y -= 500.f * DeltaTime;
	if (KEY_Triggered(EKEY::DOWN))
		m_LookAt.y += 500.f * DeltaTime;
	if (KEY_Triggered(EKEY::LEFT))
		m_LookAt.x -= 500.f * DeltaTime;
	if (KEY_Triggered(EKEY::RIGHT))
		m_LookAt.x += 500.f * DeltaTime;


	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	CalDiff();
}

void CCamera::CalDiff()
{
	// 이전 LookAt과 현재 Look의 차이값을 보정해서 현재의 LookAt을 구한다.
	
	m_AccTime += DeltaTime;

	if (m_AccTime >= m_Time)
	{
		m_CurLookAt = m_LookAt;
	}
	else
	{
		FVector2D LookDir = m_LookAt - m_PrevLookAt;
		if (!LookDir.IsZero())
		{
			m_CurLookAt = m_PrevLookAt + LookDir.Normalize() * m_Speed * DeltaTime;
		}

		
	}

	FVector2D Resoultion = CCore::GetInst()->GetResolution();
	FVector2D Center = Resoultion / 2.f;



	m_Diff = m_CurLookAt - Center;
	m_PrevLookAt = m_CurLookAt;
}
