#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
public:
    CPanelUI();
    ~CPanelUI();

private:
    FVector2D       m_DragStart;

public:
    virtual void update();
    virtual void render(HDC _dc);


    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUP();
    virtual void MouseLbtnClicked();
    
    CLONE(CPanelUI);

};

