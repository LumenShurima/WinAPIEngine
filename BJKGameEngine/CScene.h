#pragma once


// ���漱��
// ������ Ÿ������ �ۿ� ��� �Ұ�
class CObject;

class CScene
{
private:
	vector<CObject*> m_Objects[(UINT)GROUP_TYPE::END]; // ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring m_strName; // Scene �̸�

	UINT			m_TileX;	// ���� ����
	UINT			m_TileY;	// ���� ����
public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	UINT GetTileX() { return m_TileX; }
	UINT GetTileY() { return m_TileY; }

	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	virtual void Enter() = 0;	// �ش� Scene�� ���� �� ȣ��
	virtual void Exit() = 0;	// �ش� Scene�� ���� �� ȣ��

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) { m_Objects[(UINT)_eType].push_back(_pObj); }
	
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType){return m_Objects[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _objGroup);
	void DeleteAll();

	void CreateTile(UINT _xCount, UINT _yCount);
	void LoadTile(const wstring& _strRelativePath);
	// vector<CObject*>& GetUIGroup() { return m_Objects[(UINT)GROUP_TYPE::UI]; }


public:
	CScene();
	virtual ~CScene();
};

