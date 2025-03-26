#include "pch.h"
#include "CResourceManager.h"

#include "CTexture.h"
#include "CPathManager.h"

CResourceManager::CResourceManager()
{

}

CResourceManager::~CResourceManager()
{
    map<wstring, CTexture*>::iterator iter = m_mapTexture.begin();
    for (; iter != m_mapTexture.end(); ++iter)
    {
        delete iter->second;
    }
}

CTexture* CResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CTexture* pTexture = FindTexture(_strKey);
    if (nullptr != pTexture)
    {
        return pTexture;
    }

    wstring strFilePath = CPathManager::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    pTexture = new CTexture;
    pTexture->Load(strFilePath);
    pTexture->SetKey(_strKey);
    pTexture->SetRelativePath(_strRelativePath);

    m_mapTexture.insert(make_pair(_strKey, pTexture));

    return pTexture;
}

CTexture* CResourceManager::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTexture.find(_strKey);
    if (iter == m_mapTexture.end())
    {
        return nullptr;
    }
    
    return iter->second;
}
