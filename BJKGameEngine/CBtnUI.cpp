#include "pch.h"
#include "CBtnUI.h"

CBtnUI::CBtnUI()
	: CUI(false)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUP()
{
}

void CBtnUI::MouseLbtnClicked()
{
	
	for (int i = 0; i < m_pFunc.size(); ++i)
	{
		m_pFunc[i]();
	}
	
}

void CBtnUI::BindMouseLbtnClicked(std::function<void()> _func)
{
	m_pFunc.push_back(_func);
}
