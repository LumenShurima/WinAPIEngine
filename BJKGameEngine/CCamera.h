#pragma once


class CObject;

class CCamera
{
	SINGLETON(CCamera)
private:
	FVector2D		m_LookAt;			// 카메라가 보는 위치
	FVector2D		m_CurLookAt;		// 이전위치와 현재 위치 보정 위치
	FVector2D		m_PrevLookAt;		// 카메라가 보는 이전 프레임 위치


	CObject*		m_pTargetObject;	// 카메라 타겟 오브젝트

	FVector2D		m_Diff;				// 해상도 중심위치와, 카메라 LookAt 간의 차이 값

	float			m_Time;				// 타겟을 따라가는데 걸리는 시간
	float			m_Speed;			// 타겟을 따라가는 속도
	float			m_AccTime;			// 누적 시간

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

