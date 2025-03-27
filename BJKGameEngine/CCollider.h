#pragma once

class CObject;


class CCollider
{
public:
	CCollider();
	~CCollider();
private:
	CObject* m_pOwner;		// collider�� �����ϰ� �ִ� ������Ʈ

	FVector2D m_OffsetPos;	// ������Ʈ�� ���� ������� ��ġ
	FVector2D m_FinalPos;	// finalupdate ���� �� �����Ӹ��� ���
	FVector2D m_Scale;		// �浹ü�� ũ��

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

