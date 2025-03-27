#pragma once


class CCollider;

class CObject
{
public:
	CObject();
	virtual ~CObject();

private:
	FVector2D	m_vPos;
	FVector2D	m_vScale;

	CCollider* m_pCollider;
	
public:
	void SetPos(FVector2D _vPos) { m_vPos = _vPos; }
	void SetScale(FVector2D _vScale) { m_vScale = _vScale; }


	FVector2D GetPos() { return m_vPos; }
	FVector2D GetScale() { return m_vScale; }

	CCollider* GetCollider() { return m_pCollider; }

	void CreateCollider();

public:
	virtual void update() = 0;
	virtual void finalupdate() final;
	virtual void render(HDC _dc);

	void ComponentRender(HDC _dc);


};

