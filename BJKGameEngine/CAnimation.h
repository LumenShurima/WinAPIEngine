#pragma once

class CAnimator;
class CTexture;


struct FAnimFrame
{
    FVector2D   LT;
    FVector2D   Slice;
    FVector2D   Offset;
    float       Length;
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
    int                 m_CurFrame;         // ���� ������
    float               m_Time;             // �ð� ���� ����

    bool                m_bFinish;           // ��� �Ϸ� ����

    void SetName(const wstring& _strName) { m_strName = _strName; }
    

public:
    
    void SetFrame(int _FrameIdx)
    {
        m_bFinish = false;
        m_CurFrame = _FrameIdx;
        m_Time = 0.f;
    }
    const wstring& GetName() { return m_strName; }
    bool IsFinish() { return m_bFinish; }
    
    FAnimFrame& GetFrame(int _Idx) { return m_Frames[_Idx]; }
    int GetMaxFrame() { return (int)(m_Frames.size()); }
    void Create(CTexture* _pTexture, FVector2D _LT, FVector2D _SliceSize, FVector2D _step,float _Length, UINT _FrameCount);
public:
    void update();
    void render(HDC _dc);

    
};

