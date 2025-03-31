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
#include "CCollider.h"
#include "CAnimator.h"


CPlayer::CPlayer()
	: m_pTexture(nullptr)
{
	// Texture 로딩하기
	// m_pTexture = CResourceManager::GetInst()->LoadTexture(L"PlayerTexture", L"texture\\Plane.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(FVector2D(0.f, 12.f));
	GetCollider()->SetScale(FVector2D(20.f, 40.f));


	// Texture 로딩하기
	m_pTexture = CResourceManager::GetInst()->LoadTexture(L"PlayerTexture", L"texture\\link.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(m_pTexture
		, FVector2D(0.f, 260.f)
		, FVector2D(60.f, 65.f)
		, FVector2D(60.f, 0.f), 10);
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

	// 컴포넌트(충돌체, etc....)가 있으면 추가
	ComponentRender(_dc);
}

void CPlayer::CreateMissile()
{
	FVector2D MissilePos = GetPos();
	MissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(MissilePos);
	pMissile->SetScale(FVector2D(25.f, 25.f));
	pMissile->SetDir(FVector2D(0.f, -1.f));

	CreateObject(pMissile, GROUP_TYPE::PROJECTILE_PLAYER);
}
