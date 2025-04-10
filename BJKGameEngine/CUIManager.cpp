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
	// 1. FocusedUI 확인
	m_pFocusedUI = GetFocusedUI();
	
	if (!m_pFocusedUI)
		return;
	

	CUI* pUI = m_pFocusedUI;

	// 부모 UI 포함, 자식 UI 들 중 실제 타겟 된 UI를 가져온다.
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
	// 이미 포커싱 중인 경우 또는 포커싱 해제요청인 경우
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

	// 1. 부모 UI 포함, 모든 자식들을 감지한다.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> NoneTargets;

	queue.clear();
	NoneTargets.clear();

	queue.push_back(_pParentUI);
	

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();


		// 큐에서 꺼내온 UI가 TargetUI인지 확인
		// 타겟 UI 들 중, 더 우선 순위가 높은 기준은 더 낮은 계층의 자식 UI
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


	// 기존 포커싱 UI를 받아두고 변경되었는지 확인한다.
	CUI* pFocuedUI = m_pFocusedUI;

	if (!(KEY_Started(EKEY::LBTN)))
	{
		return pFocuedUI;
	}


	// 왼쪽버튼 Down이 발생했다는 전제
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter < vecUI.end() ; ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}

	}
	
	// 이번에 Focus된 UI가 없다
	if(vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocuedUI = (CUI*)*targetiter;

	vecUI.erase(targetiter);

	vecUI.push_back(pFocuedUI);

	return pFocuedUI;
}
