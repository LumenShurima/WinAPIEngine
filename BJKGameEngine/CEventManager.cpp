#include "pch.h"
#include "CEventManager.h"
#include "CObject.h"

#include "CSceneManager.h"
#include "CScene.h"

CEventManager::CEventManager()
{

}

CEventManager::~CEventManager()
{

}

void CEventManager::update()
{
	// 이전 프레임에 등록된 Killed Object들을 삭제한다.
	for (size_t i = 0; i < m_Killed.size(); ++i)
	{
		delete m_Killed[i];
	}
	m_Killed.clear();


	// Event 처리
	for (size_t i = 0; i < m_Events.size(); ++i)
	{
		Execute(m_Events[i]);
	}
	m_Events.clear();
}

void CEventManager::Execute(const FEvent _event)
{
	switch (_event.Event)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam : Group Type
		CObject* NewObj= (CObject*)_event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_event.wParam;

		CSceneManager::GetInst()->GetCurrentScene()->AddObject(NewObj, eType);
	}
		break;
	
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Address
		// Object 를 Kill 대기 상태로 변경
		// Kill 예정 오브젝트를 모아둔다.
		CObject* pKilledObj = (CObject*)_event.lParam;
		pKilledObj->SetKilled();
		m_Killed.push_back(pKilledObj);

	}


		break;
	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : Next Scene Type
		CSceneManager::GetInst()->ChangeOtherScene((SCENE_TYPE)_event.lParam);


		break;
	
	}
}


