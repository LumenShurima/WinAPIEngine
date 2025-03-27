#pragma once

class CObject;


class CCollider
{
public:
	CCollider();
	~CCollider();
private:
	CObject* m_pOwner;		// collider를 소유하고 있는 오브젝트

	FVector2D m_OffsetPos;	// 오브젝트로 부터 상대적인 위치
	FVector2D m_FinalPos;	// finalupdate 에서 매 프레임마다 계산
	FVector2D m_Scale;		// 충돌체의 크기

public:
	void SetOffsetPos(FVector2D _Pos) { m_OffsetPos = _Pos; }
	void SetScale(FVector2D _Scale) { m_Scale = _Scale; }

	FVector2D GetOffsetPos() { return m_OffsetPos; }
	FVector2D GetScale() { return m_Scale; }
public:
	void FinalUpdate();
	void render(HDC _dc);

	friend class CObject;
};

