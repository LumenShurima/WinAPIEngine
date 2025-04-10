#pragma once


class CObject;

class CCamera
{
	SINGLETON(CCamera)
private:
	FVector2D		m_LookAt;			// ī�޶� ���� ��ġ
	FVector2D		m_CurLookAt;		// ������ġ�� ���� ��ġ ���� ��ġ
	FVector2D		m_PrevLookAt;		// ī�޶� ���� ���� ������ ��ġ


	CObject*		m_pTargetObject;	// ī�޶� Ÿ�� ������Ʈ

	FVector2D		m_Diff;				// �ػ� �߽���ġ��, ī�޶� LookAt ���� ���� ��

	float			m_Time;				// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float			m_Speed;			// Ÿ���� ���󰡴� �ӵ�
	float			m_AccTime;			// ���� �ð�

public:
	void SetLookAt(FVector2D _Look)
	{ 
		m_LookAt = _Look; 
		float MoveDistance = (m_LookAt - m_PrevLookAt).Length();
		m_Speed = MoveDistance / m_Time;
		m_AccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObject = _pTarget; }
	FVector2D GetLookAt() { return m_CurLookAt; }
	FVector2D GetRenderPos(FVector2D _ObjPos) {return _ObjPos - m_Diff;}
	FVector2D GetRealPos(FVector2D _RealPos) { return _RealPos + m_Diff; }

public:
	void update();


private:
	void CalDiff();



};

