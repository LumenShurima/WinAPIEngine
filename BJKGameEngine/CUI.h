#pragma once
#include "CObject.h"


class CUI :
    public CObject
{
private:
    vector<CUI*>    m_ChildUI;
    CUI*            m_pParentUI;

    FVector2D       m_FinalPos;

    bool            m_bCamAffected; // UI가 카메라 영향을 받는지
    bool            m_bMouseOn;     // UI 위에 마우스가 있는지
    bool            m_bLbtnDown;    // UI 에 왼쪽버툰이 눌린적 있는지
public:
    FVector2D GetFinal() { return m_FinalPos; }



    CUI* GetParent() { return m_pParentUI; }
    void AddChild(CUI* _pUI) {m_ChildUI.push_back(_pUI);_pUI->m_pParentUI = this;}
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnDown() { return m_bLbtnDown; }
    const vector<CUI*>& GetChildUI() { return m_ChildUI; }



public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);

    void MouseOnCheck();
public:
    virtual void MouseOn();

    virtual void MouseLbtnDown();
    virtual void MouseLbtnUP();
    virtual void MouseLbtnClicked();

    virtual CUI* Clone() = 0;
public:
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();


    friend class CUIManager;
};

