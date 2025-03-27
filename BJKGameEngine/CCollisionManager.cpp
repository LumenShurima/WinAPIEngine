#include "pch.h"
#include "CCollisionManager.h"
#include "CSceneManager.h"
#include "CScene.h"

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

void CCollisionManager::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
}

