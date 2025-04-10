#pragma once
#include "CUI.h"




class CBtnUI :
    public CUI
{
public:
    CBtnUI();
    ~CBtnUI();

private:
    vector<std::function<void()>> m_pFunc;

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUP();
    virtual void MouseLbtnClicked();


    // How to Using Func Binding
    // ((Class*)InstanceClassName)->BindMouseLbtnClicked([&]() { /**Func**/; });
    void BindMouseLbtnClicked(std::function<void()> _func);
   
    CLONE(CBtnUI);
};

