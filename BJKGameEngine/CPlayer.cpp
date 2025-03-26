#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "CTexture.h"
#include "CPathManager.h"
#include "CResourceManager.h"

CPlayer::CPlayer()
	: m_pTexture(nullptr)
{
	// Texture 로딩하기
	m_pTexture = CResourceManager::GetInst()->LoadTexture(L"PlayerTexture", L"texture\\Plane.bmp");

}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	FVector2D Pos = GetPos();
	if (KEY_Triggered(EKEY::W))
	{
		Pos.y -= 200.f * DeltaTime;
	}
	if (KEY_Triggered(EKEY::S))
	{
		Pos.y += 200.f * DeltaTime;
	}
	if (KEY_Triggered(EKEY::A))
	{
		Pos.x -= 200.f * DeltaTime;
	}
	if (KEY_Triggered(EKEY::D))
	{
		Pos.x += 200.f * DeltaTime;
	}

	if (KEY_Started(EKEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(Pos);
}

void CPlayer::render(HDC _dc)
{
	int Width = (int)m_pTexture->Width();
	int Height = (int)m_pTexture->Height();
	// 188 x 268
	
	FVector2D Pos = GetPos();

	/*BitBlt(_dc
		, int(Pos.x - (float)(Width / 2))
		, int(Pos.y - (float)(Height / 2))
		, Width, Height
		, m_pTexture->GetDC()
		, 0,0 ,SRCCOPY);*/

	TransparentBlt(_dc
		, int(Pos.x - (float)(Width / 2))
		, int(Pos.y - (float)(Height / 2))
		, Width, Height
		, m_pTexture->GetDC()
		, 0, 0, Width, Height
		, RGB(255,0,255));
}

void CPlayer::CreateMissile()
{
	FVector2D MissilePos = GetPos();
	MissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;

	pMissile->SetPos(MissilePos);
	pMissile->SetScale(FVector2D(25.f, 25.f));
	pMissile->SetDir(FVector2D(0.f, -1.f));

	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	pCurScene->AddObject(pMissile);
}
