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
		// �浹ü�� �������� �ʴ� ��� ��� ����
		if (nullptr == vectorLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vectorRight.size(); ++j)
		{
			// �浹ü�� ���ų�, �����ο� �浹�� ���
			if (nullptr == vectorRight[j]->GetCollider() ||
				vectorLeft[i] == vectorRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vectorLeft[i]->GetCollider();
			CCollider* pRightCol = vectorRight[j]->GetCollider();


			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);
			
			// �浹 ������ �� ��� ������ ��� ���(�浹���� �ʾҴٷ� �⺻ ����)
			if (m_mapColInfo.end() == iter)
			{
				iter = m_mapColInfo.insert(make_pair(ID.ID, false)).first;
			}

			if(IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹 ��.

				if (iter->second)
				{
					// �������� �浹 ����

					if (vectorLeft[i]->IsKilled() || vectorRight[j]->IsKilled())
					{
						// �ٵ� ���� �ϳ��� ���� �����̶��, �浹 ���� ������
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
					// ������ �浹���� ����
					// ���� �ϳ��� ���� �����̶��, �浹 ����
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
				// ���� �浹�ϰ� ���� ����
				if (iter->second)
				{
					// �������� �浹�ϰ� �־���.
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ���

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



