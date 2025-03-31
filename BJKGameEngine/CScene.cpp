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
			// ������Ʈ �迭�� �׷� ������ j��ü ����;
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

// ������Ʈ���� ������Ʈ �� ����Ǿ�� �ϴ� 
// �۾����� ���������� ������Ʈ �����ݴϴ�.
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
