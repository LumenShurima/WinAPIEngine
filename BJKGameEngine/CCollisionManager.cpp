#include "pch.h"
#include "CCollisionManager.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"



CCollisionManager::CCollisionManager()
	: m_arrCheck{}
{
	
}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::init()
{
}

void CCollisionManager::update()
{
	for (UINT Row = 0; Row < (UINT)GROUP_TYPE::END; ++Row)
	{
		m_arrCheck[Row];
		for (UINT Col = Row; Col < (UINT)GROUP_TYPE::END; ++Col)
		{
			if (m_arrCheck[Row] & (1 << Col))
			{
				CollisionGroupUpdate((GROUP_TYPE)Row, (GROUP_TYPE)Col);
			}
		}

	}
}

void CCollisionManager::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	const vector<CObject*>& vectorLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vectorRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vectorLeft.size(); ++i)
	{
		// 충돌체를 보유하지 않는 경우 계산 생략
		if (nullptr == vectorLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vectorRight.size(); ++j)
		{
			// 충돌체가 없거나, 스스로와 충돌한 경우
			if (nullptr == vectorRight[j]->GetCollider() ||
				vectorLeft[i] == vectorRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vectorLeft[i]->GetCollider();
			CCollider* pRightCol = vectorRight[j]->GetCollider();


			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);
			
			// 충돌 정보가 미 등록 상태인 경우 등록(충돌하지 않았다로 기본 세팅)
			if (m_mapColInfo.end() == iter)
			{
				iter = m_mapColInfo.insert(make_pair(ID.ID, false)).first;
			}

			if(IsCollision(pLeftCol, pRightCol))
			{
				// 현재 충돌 중.

				if (iter->second)
				{
					// 이전에도 충돌 했음

					if (vectorLeft[i]->IsKilled() || vectorRight[j]->IsKilled())
					{
						// 근데 둘중 하나가 삭제 예정이라면, 충돌 해제 시켜줌
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}

				}
				else
				{
					// 이전에 충돌하지 않음
					// 둘중 하나가 삭제 예정이라면, 충돌 무시
					if (!vectorLeft[i]->IsKilled() && !vectorRight[j]->IsKilled())
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				// 현재 충돌하고 있지 않음
				if (iter->second)
				{
					// 이전에는 충돌하고 있었다.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false; 
				}

			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	FVector2D LeftPos = _pLeftCol->GetFinalPos(); 
	FVector2D LeftScale = _pLeftCol->GetScale(); 

	FVector2D RightPos = _pRightCol->GetFinalPos();
	FVector2D RightScale = _pRightCol->GetScale();
	

	if (abs(RightPos.x - LeftPos.x) < (LeftScale.x + RightScale.x) / 2.f
		&& abs(RightPos.y - LeftPos.y) < (LeftScale.y + RightScale.y) / 2.f)
	{
		return true;
	}
	return false;
}

void CCollisionManager::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트)로 사용

	UINT Row = (UINT)_eLeft;
	UINT Col = (UINT)_eRight;

	if (Col < Row)
	{
		Row = (UINT)_eRight;
		Col = (UINT)_eLeft;
	}

	if (m_arrCheck[Row] & (1 << Col))
	{
		m_arrCheck[Row] &= ~(1 << Col);
	}
	else
	{
		m_arrCheck[Row] |= (1 << Col);
	}
	

}



