#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
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

}

void CCollider::render(HDC _dc)
{
	SelectGDI temp1(_dc, PEN_TYPE::GREEN);
	SelectGDI temp2(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, (int)(m_FinalPos.x - m_Scale.x / 2.f)
		, (int)(m_FinalPos.y - m_Scale.y / 2.f)
		, (int)(m_FinalPos.x + m_Scale.x / 2.f)
		, (int)(m_FinalPos.y + m_Scale.y / 2.f));

}
