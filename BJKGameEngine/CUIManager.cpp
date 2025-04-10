#include "pch.h"
#include "CUIManager.h" 

#include "CSceneManager.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyManager.h"

CUIManager::CUIManager()
	: m_pFocusedUI(nullptr)
{

}

CUIManager::~CUIManager()
{

}

void CUIManager::update()
{
	// 1. FocusedUI Ȯ��
	m_pFocusedUI = GetFocusedUI();
	
	if (!m_pFocusedUI)
		return;
	

	CUI* pUI = m_pFocusedUI;

	// �θ� UI ����, �ڽ� UI �� �� ���� Ÿ�� �� UI�� �����´�.
	pUI = GetTargetdUI(pUI);

	if (nullptr != pUI)
	{
		pUI->MouseOn();

		if (KEY_Started(EKEY::LBTN))
		{
			pUI->MouseLbtnDown();
			pUI->m_bLbtnDown = true;
		}
		else if (KEY_Completed(EKEY::LBTN))
		{
			if (pUI->m_bLbtnDown)
			{
				pUI->MouseLbtnClicked();
			}

			pUI->MouseLbtnUP();
			pUI->m_bLbtnDown = false;
		}
	}
	
}

void CUIManager::SetFocusedUI(CUI* _pUI)
{
	// �̹� ��Ŀ�� ���� ��� �Ǵ� ��Ŀ�� ������û�� ���
	if (m_pFocusedUI == _pUI || nullptr == m_pFocusedUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}


	m_pFocusedUI = _pUI;


	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	vector<CObject*>& vecUI = const_cast<vector<CObject*>&>(pCurScene->GetGroupObject(GROUP_TYPE::UI));

	vector<CObject*>::iterator iter = vecUI.begin();
	if (iter != vecUI.end())
	{
		for (; iter < vecUI.end(); ++iter)
		{
			if (m_pFocusedUI == *iter)
			{
				break;
			}
		}

		vecUI.erase(iter);
		vecUI.push_back(m_pFocusedUI);
	}

}

CUI* CUIManager::GetTargetdUI(CUI* _pParentUI)
{

	// 1. �θ� UI ����, ��� �ڽĵ��� �����Ѵ�.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> NoneTargets;

	queue.clear();
	NoneTargets.clear();

	queue.push_back(_pParentUI);
	

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();


		// ť���� ������ UI�� TargetUI���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱 ������ ���� ������ �� ���� ������ �ڽ� UI
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				NoneTargets.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			NoneTargets.push_back(pUI);
		}
		
		const vector<CUI*>& Childs= pUI->GetChildUI();
		for (size_t i = 0; i < Childs.size(); ++i)
		{
			queue.push_back(Childs[i]);
		}
		
	}

	if (KEY_Completed(EKEY::LBTN))
	{
		for (size_t i = 0; i < NoneTargets.size(); ++i)
		{
			NoneTargets[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;

}

CUI* CUIManager::GetFocusedUI()
{
	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	vector<CObject*>& vecUI = const_cast<vector<CObject*>&>(pCurScene->GetGroupObject(GROUP_TYPE::UI));


	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ����Ǿ����� Ȯ���Ѵ�.
	CUI* pFocuedUI = m_pFocusedUI;

	if (!(KEY_Started(EKEY::LBTN)))
	{
		return pFocuedUI;
	}


	// ���ʹ�ư Down�� �߻��ߴٴ� ����
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter < vecUI.end() ; ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}

	}
	
	// �̹��� Focus�� UI�� ����
	if(vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocuedUI = (CUI*)*targetiter;

	vecUI.erase(targetiter);

	vecUI.push_back(pFocuedUI);

	return pFocuedUI;
}
