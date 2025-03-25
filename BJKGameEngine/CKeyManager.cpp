#include "pch.h"
#include "CKeyManager.h"

#include "CCore.h"

int g_arrVK[(int)EKEY::FinalEND] =
{
	VK_LEFT,	// LEFT,
	VK_RIGHT,	// RIGHT,
	VK_UP,		// UP,
	VK_DOWN,	// DOWN,
	 'Q',
	 'W',
	 'E',
	 'R',
	 'T',
	 'Y',
	 'U',
	 'I',
	 'O',
	 'P',
	 'A',
	 'S',
	 'D',
	 'F',
	 'G',
	 'Z',
	 'X',
	 'C',
	 'V',
	 'B',
	 VK_MENU,	// ALT
	 VK_CONTROL, 
	 VK_LSHIFT, 
	 VK_SPACE, 
	 VK_RETURN,	// ENTER 
	 VK_ESCAPE, 


	 // FinalEND
};




CKeyManager::CKeyManager()
{

}

CKeyManager::~CKeyManager()
{

}

void CKeyManager::init()
{
	for (int i = 0; i < (int)EKEY::FinalEND; ++i)
	{
		m_Keys.push_back(FKeyInfo{ EKEY_STATE::NONE, false });
	}

}

void CKeyManager::update()
{
	// 윈도우 포커싱 알아내기
	// HWND hMainWnd = CCore::GetInst()->getMainHwnd();
	HWND hWnd = GetFocus();

	// 윈도우 포커싱 중일 때 키 이벤트 동작
	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)EKEY::FinalEND; ++i)
		{
			// 키가 눌렸을 떄
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_Keys[i].bPressed)
				{
					// 이전에도 눌렸음
					m_Keys[i].eState = EKEY_STATE::Triggered;
				}
				else
				{
					// 이전에 눌린적 없음
					m_Keys[i].eState = EKEY_STATE::Started;
				}

				m_Keys[i].bPressed = true;
			}

			// 키가 안 눌려져있다
			else
			{
				if (m_Keys[i].bPressed)
				{
					// 이전에 눌려있었다.
					m_Keys[i].eState = EKEY_STATE::Completed;
				}
				else
				{
					// 이전에도 안 눌려있었다
					m_Keys[i].eState = EKEY_STATE::NONE;
				}

				m_Keys[i].bPressed = false;
			}

		}
	}
	else
	{
		for (int i = 0; i < (int)EKEY::FinalEND; ++i)
		{
			m_Keys[i].bPressed = false;

			if (EKEY_STATE::Started == m_Keys[i].eState || EKEY_STATE::Triggered == m_Keys[i].eState)
			{
				m_Keys[i].eState = EKEY_STATE::Completed;
			}
			else if (EKEY_STATE::Completed == m_Keys[i].eState)
			{
				m_Keys[i].eState = EKEY_STATE::NONE;
			}
		}
	}
}
