#pragma once
#include "CResource.h"


class CTexture :
    public CResource
{
private:
    CTexture();
    virtual ~CTexture();
public:
    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }
    HDC GetDC() { return m_dc; }
private:
    HDC m_dc;
    HBITMAP m_hBit;
    BITMAP m_bitInfo;

private:
    void Load(const wstring& _strfilePath);

    friend class CResourceManager;



};

