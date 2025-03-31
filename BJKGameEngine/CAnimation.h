#pragma once

class CAnimator;
class CTexture;


struct FAnimFrame
{
    FVector2D LT;

};


class CAnimation

{
public:
    CAnimation();
    ~CAnimation();

    friend class CAnimator;

private:
    wstring             m_strName;
    CAnimator*          m_pAnimator;
    CTexture*           m_pTexture;         // Animation�� ����ϴ� �ؽ�ó
    vector<FAnimFrame>  m_Frames;           // ��� ������ ����

    void SetName(const wstring& _strName) { m_strName = _strName; }

public:
    
    const wstring& GetName() { return m_strName; }
    void Create(CTexture* _pTexture, FVector2D _LT, FVector2D _SliceSize, FVector2D _step, UINT _FrameCount);
public:
    void update();
    void render(HDC _dc);

    
};

