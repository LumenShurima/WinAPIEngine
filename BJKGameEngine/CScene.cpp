#include "pch.h"
#include "CScene.h"
#include "CObject.h"


void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_Objects[i].size(); ++j)
		{
			m_Objects[i][j]->update();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_Objects[i].size(); ++j)
		{
			m_Objects[i][j]->render(_dc);
		}
	}
}

CScene::CScene()
{

}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_Objects[i].size(); ++j)
		{
			// 오브젝트 배열의 그룹 벡터의 j물체 삭제;
			delete m_Objects[i][j];
		}
	}
	
}

