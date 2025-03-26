#include "pch.h"
#include "CPathManager.h"

#include "CCore.h"

CPathManager::CPathManager()
	: m_szContentPath{}
{

}

CPathManager::~CPathManager()
{

}


void CPathManager::init()
{
	GetCurrentDirectory(255, m_szContentPath);
	
	int Len = wcslen(m_szContentPath);


	// 상위폴더로
	for (int i = Len - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\binary\\content\\");
	// + binary\\content\\

	
	// SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}
