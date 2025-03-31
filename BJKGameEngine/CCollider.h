#pragma once

class CObject;


class CCollider
{
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();
private:
	static UINT g_NextID;

	CObject* m_pOwner;		// collider를 소유하고 있는 오브젝트

	FVector2D m_OffsetPos;	// 오브젝트로 부터 상대적인 위치
	FVector2D m_FinalPos;	// finalupdate 에서 매 프레임마다 계산
	FVector2D m_Scale;		// 충돌체의 크기


	UINT m_ID;				// 충돌체 고유한 ID 값
	int m_Col;
public:
	void SetOffsetPos(FVector2D _Pos) { m_OffsetPos = _Pos; }
	void SetScale(FVector2D _Scale) { m_Scale = _Scale; }

	FVector2D GetOffsetPos() { return m_OffsetPos; }
	FVector2D GetScale() { return m_Scale; }
	FVector2D GetFinalPos() { return m_FinalPos; }

	CObject* GetOwner() { return m_pOwner; }

	UINT GetID() { return m_ID; }
public:
	void FinalUpdate();
	void render(HDC _dc);


public:
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther);		// 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);	// 충돌 진입시
	void OnCollisionExit(CCollider* _pOther);	// 충돌 해제 

	// Default 대입 연산자 삭제
	// 같은 Collider 타입 대입 방지
	CCollider& operator = (CCollider& _origin) = delete;

	friend class CObject;
};

