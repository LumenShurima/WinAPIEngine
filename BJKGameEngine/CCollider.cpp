#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT CCollider::g_NextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_ID(g_NextID++)
	, m_Col(0)
{

}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)
	, m_OffsetPos(_origin.m_OffsetPos)
	, m_Scale(_origin.m_Scale)
	, m_ID(g_NextID++)
{
	
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	// Object À§Ä¡ follow
	FVector2D ObjectPos = m_pOwner->GetPos();
	m_FinalPos = ObjectPos + m_OffsetPos;

	assert(0 <= m_Col);
}

void CCollider::render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_Col)
	{
		ePen = PEN_TYPE::RED;
	}

	SelectGDI temp1(_dc, ePen);
	SelectGDI temp2(_dc, BRUSH_TYPE::HOLLOW);
	
	Rectangle(_dc
		, (int)(m_FinalPos.x - m_Scale.x / 2.f)
		, (int)(m_FinalPos.y - m_Scale.y / 2.f)
		, (int)(m_FinalPos.x + m_Scale.x / 2.f)
		, (int)(m_FinalPos.y + m_Scale.y / 2.f));

}

void CCollider::OnCollision(CCollider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_Col;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_Col;
	m_pOwner->OnCollisionExit(_pOther);
}
