#pragma once
#include "CObject.h"

class CTexture;


class CTile :
    public CObject
{

private:
    CTexture*   m_pTileTexture;
    int         m_Index;

public:
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTexture = _pTex;
    }
    void SetIndex(int _Index){m_Index = _Index;}
    int GetIndex() { return m_Index; }
    void AddIndex()
    {
        m_Index++;
    }

public:
    CTile();
    ~CTile();


private:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    CLONE(CTile);


};

