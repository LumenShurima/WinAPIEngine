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
	
	int Len = (int)wcslen(m_szContentPath);


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

wstring CPathManager::GetRelativePath(const wchar_t* _filePath)
{

	wstring strFilePath = _filePath;

	size_t AbsloutePath = wcslen(m_szContentPath);
	size_t FullPath = strFilePath.length();


	wstring strRelativePath = strFilePath.substr(AbsloutePath, FullPath - AbsloutePath);


	return strRelativePath;
}
