#include "pch.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResourceManager.h"
#include "CPathManager.h"


CScene::CScene()
	: m_TileX(0)
	, m_TileY(0)
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

void CScene::CreateTile(UINT _xCount, UINT _yCount)
{
	DeleteGroup(GROUP_TYPE::TILE);
	m_TileX = _xCount;
	m_TileY = _yCount;

	CTexture* pTileTexture = CResourceManager::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\TILE.bmp");

	for (UINT i = 0; i < _xCount; ++i)
	{
		for (UINT j = 0; j < _yCount; ++j)
		{
			CTile* pTile = new CTile;

			pTile->SetPos(FVector2D((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTexture);
			
			

			AddObject(pTile, GROUP_TYPE::TILE);

		}
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// File은 커널 오브젝트
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// 타일 가로세로 개수 저장
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	CreateTile(xCount, yCount);

	// 모든 타일들을 개별적으로 저장된 데이터를 불러오기
	const vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}
