#include "pch.h"
#include "CScene.h"
#include "CObject.h"




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

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_Objects[i].size(); ++j)
		{
			if (!m_Objects[i][j]->IsKilled())
			{
				m_Objects[i][j]->update();
			}
		}
	}
}

// 오브젝트들의 업데이트 후 보장되어야 하는 
// 작업들을 마지막으로 업데이트 시켜줍니다.
void CScene::finalupdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_Objects[i].size(); ++j)
		{
			m_Objects[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_Objects[i].begin();

		for (; iter != m_Objects[i].end();)
		{
			if (!(*iter)->IsKilled())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_Objects[i].erase(iter);
			}
		}
	}
}


void CScene::DeleteGroup(GROUP_TYPE _objGroup)
{
	Safe_Delete_Vec<CObject*>(m_Objects[(UINT)_objGroup]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}
