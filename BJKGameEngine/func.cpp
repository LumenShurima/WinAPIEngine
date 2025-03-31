#include "pch.h"
#include "func.h"

#include "CEventManager.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	FEvent Event = {};
	Event.Event = EVENT_TYPE::CREATE_OBJECT;
	Event.lParam = (DWORD_PTR)_pObj;
	Event.wParam = (DWORD_PTR)_eGroup;

	CEventManager::GetInst()->AddEvent(Event);
}

void DeleteObject(CObject* _pObj)
{
	FEvent Event = {};
	Event.Event = EVENT_TYPE::DELETE_OBJECT;
	Event.lParam = (DWORD_PTR)_pObj;

	CEventManager::GetInst()->AddEvent(Event);
}

void ChangeScene(SCENE_TYPE _Scene)
{
	FEvent Event = {};
	Event.Event = EVENT_TYPE::SCENE_CHANGE;
	Event.lParam = (DWORD_PTR)_Scene;

	CEventManager::GetInst()->AddEvent(Event);
}
