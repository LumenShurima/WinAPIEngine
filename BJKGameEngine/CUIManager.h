#pragma once

class CUI;

class CUIManager
{
	SINGLETON(CUIManager);
private:
	CUI* m_pFocusedUI;


public:
	void update();


	void SetFocusedUI(CUI* _pUI);
private:
	// 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 변환한다.
	CUI* GetTargetdUI(CUI* _pParentUI); 

	// 현재 포커싱 된 UI를 찾는다.
	CUI* GetFocusedUI();
	
};

