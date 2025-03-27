#pragma once


// ���漱��
// ������ Ÿ������ �ۿ� ��� �Ұ�
class CObject;

class CScene
{
private:
	vector<CObject*> m_Objects[(UINT)GROUP_TYPE::END]; // ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring m_strName; // Scene �̸�


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


	void update();
	void finalupdate();
	void render(HDC _dc);

	virtual void Enter() = 0;	// �ش� Scene�� ���� �� ȣ��
	virtual void Exit() = 0;	// �ش� Scene�� ���� �� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType = GROUP_TYPE::DEFAULT) { m_Objects[(UINT)_eType].push_back(_pObj); }



public:
	CScene();
	virtual ~CScene();
};

