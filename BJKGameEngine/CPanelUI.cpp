#include "pch.h"
#include "CPanelUI.h"
#include "CKeyManager.h"


CPanelUI::CPanelUI()
	: CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::update()
{

}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);
}

void CPanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		FVector2D Diff = CurMousePos - m_DragStart;

		FVector2D CurPos = GetPos();
		CurPos += Diff;
		SetPos(CurPos);

		m_DragStart = CurMousePos;
	}
}

void CPanelUI::MouseLbtnDown()
{
	m_DragStart = CurMousePos;
}

void CPanelUI::MouseLbtnUP()
{
}

void CPanelUI::MouseLbtnClicked()
{
}
