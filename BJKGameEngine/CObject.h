#pragma once




class CObject
{
public:
	CObject();
	virtual ~CObject();

private:
	FVector2D	m_vPos;
	FVector2D	m_vScale;
	
public:
	void SetPos(FVector2D _vPos) { m_vPos = _vPos; }
	void SetScale(FVector2D _vScale) { m_vScale = _vScale; }


	FVector2D GetPos() { return m_vPos; }
	FVector2D GetScale() { return m_vScale; }

public:
	virtual void update() = 0;
	virtual void render(HDC _dc);


};

