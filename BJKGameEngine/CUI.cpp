#include "pch.h"
#include "CUI.h"

#include "CKeyManager.h"
#include "CCamera.h"
#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_pParentUI(nullptr)
	, m_FinalPos(0.f, 0.f)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
{
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_ChildUI.size(); ++i)
	{
		AddChild(_origin.m_ChildUI[i]->Clone());
	}
	
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_ChildUI);
}



void CUI::update()
{
	// child ui update
	update_child();
}

void CUI::finalupdate()
{
	CObject::finalupdate();
	m_FinalPos = GetPos();

	// UI의 최종 좌표를 구한다.
	if (this->GetParent())
	{
		FVector2D ParentPos = GetParent()->GetFinal();
		m_FinalPos += ParentPos;
	}


	// UI 위에 마우스 있는지 체크
	MouseOnCheck();

	finalupdate_child();

}

void CUI::render(HDC _dc)
{
	FVector2D Pos = GetFinal();
	FVector2D Scale = GetScale();

	if (m_bCamAffected)
	{
		Pos = CCamera::GetInst()->GetRenderPos(Pos);
	}
	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		Rectangle(_dc
			, (int)(Pos.x)
			, (int)(Pos.y)
			, (int)(Pos.x + Scale.x)
			, (int)(Pos.y + Scale.y));
	}
	else
	{
		Rectangle(_dc
			, (int)(Pos.x)
			, (int)(Pos.y)
			, (int)(Pos.x + Scale.x)
			, (int)(Pos.y + Scale.y));
	}
	// child ui render
	render_child(_dc);
}

void CUI::update_child()
{
	for (size_t i = 0; i < m_ChildUI.size(); ++i)
	{
		m_ChildUI[i]->update();
	}
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_ChildUI.size(); ++i)
	{
		m_ChildUI[i]->finalupdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_ChildUI.size(); ++i)
	{
		m_ChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	FVector2D MousePos = CurMousePos;
	FVector2D Scale = GetScale();
	if (m_bCamAffected)
	{
		MousePos = CCamera::GetInst()->GetRealPos(MousePos);
	}



	if (m_FinalPos.x <= MousePos.x && MousePos.x <= m_FinalPos.x + Scale.x
		&& m_FinalPos.y <= MousePos.y && MousePos.y <= m_FinalPos.y + Scale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

}

void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
	this;
}

void CUI::MouseLbtnUP()
{
	this;
}

void CUI::MouseLbtnClicked()
{
	this;
}
