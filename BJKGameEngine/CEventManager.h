#pragma once


struct FEvent
{
	EVENT_TYPE	Event;
	DWORD_PTR		lParam;
	DWORD_PTR		wParam;
};

class CEventManager
{
	SINGLETON(CEventManager);

private:
	vector<FEvent> m_Events;

	vector<CObject*> m_Killed;

public:
	void update();

private:
	void Execute(const FEvent _event);

public:
	void AddEvent(const FEvent& _event) { m_Events.push_back(_event); }
};

