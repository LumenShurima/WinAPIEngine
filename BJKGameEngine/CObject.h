#pragma once


class CCollider;
class CAnimator;


class CObject
{
public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

private:
	wstring			m_strName;

	FVector2D		m_vPos;
	FVector2D		m_vScale;

	CCollider*		m_pCollider;
	CAnimator* m_pAnimator;

	bool m_bAlive;
	
public:
	void SetPos(FVector2D _vPos) { m_vPos = _vPos; }
	void SetScale(FVector2D _vScale) { m_vScale = _vScale; }


	FVector2D GetPos() { return m_vPos; }
	FVector2D GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }


	bool IsKilled(){return !m_bAlive;}
	

	void CreateCollider();
	void CreateAnimator();


	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetKilled() { m_bAlive = false; }
	friend class CEventManager;

public:
	virtual void update() = 0;
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void ComponentRender(HDC _dc);
	
	virtual CObject* Clone() = 0;



};

