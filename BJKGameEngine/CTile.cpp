#include "pch.h"
#include "CTile.h"
#include "CTexture.h"

CTile::CTile()
	: m_pTileTexture(nullptr)
	, m_Index(1)
{

}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileTexture || -1 == m_Index)
		return;

	UINT Width = m_pTileTexture->Width();
	UINT Height = m_pTileTexture->Height();

	UINT MaxCol = Width / TILE_SIZE;
	UINT MaxRow = Height / TILE_SIZE;

	UINT CurRow = (UINT)m_Index / MaxCol;
	UINT CurCol = (UINT)m_Index % MaxCol;

	// 이미지 범위를 벗어난 인덱스
	if (MaxRow <= CurRow)
	{
		assert(nullptr);
	}


	FVector2D RenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	
	BitBlt(_dc
		, (int)RenderPos.x
		, (int)RenderPos.y
		, (int)TILE_SIZE
		, (int)TILE_SIZE
		, m_pTileTexture->GetDC()
		, CurCol * TILE_SIZE
		, CurRow * TILE_SIZE
		, SRCCOPY);
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_Index, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_Index, sizeof(int), 1, _pFile);
}
