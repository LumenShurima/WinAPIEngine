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

	CObject* m_pOwner;		// collider�� �����ϰ� �ִ� ������Ʈ

	FVector2D m_OffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	FVector2D m_FinalPos;	// finalupdate ���� �� �����Ӹ��� ���
	FVector2D m_Scale;		// �浹ü�� ũ��


	UINT m_ID;				// �浹ü ������ ID ��
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
	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther);		// �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);	// �浹 ���Խ�
	void OnCollisionExit(CCollider* _pOther);	// �浹 ���� 

	// Default ���� ������ ����
	// ���� Collider Ÿ�� ���� ����
	CCollider& operator = (CCollider& _origin) = delete;

	friend class CObject;
};

