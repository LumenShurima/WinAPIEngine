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
	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
	CUI* GetTargetdUI(CUI* _pParentUI); 

	// ���� ��Ŀ�� �� UI�� ã�´�.
	CUI* GetFocusedUI();
	
};

