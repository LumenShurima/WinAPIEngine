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
			// ������Ʈ �迭�� �׷� ������ j��ü ����;
			delete m_Objects[i][j];
		}
	}
	
}

