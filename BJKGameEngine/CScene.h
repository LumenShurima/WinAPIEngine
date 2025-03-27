#pragma once


// 전방선언
// 포인터 타입으로 밖에 사용 불가
class CObject;

class CScene
{
private:
	vector<CObject*> m_Objects[(UINT)GROUP_TYPE::END]; // 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring m_strName; // Scene 이름


public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }


	void update();
	void finalupdate();
	void render(HDC _dc);

	virtual void Enter() = 0;	// 해당 Scene에 진입 시 호출
	virtual void Exit() = 0;	// 해당 Scene을 나갈 시 호출

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType = GROUP_TYPE::DEFAULT) { m_Objects[(UINT)_eType].push_back(_pObj); }



public:
	CScene();
	virtual ~CScene();
};

