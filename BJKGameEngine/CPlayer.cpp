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
#include "CAnimation.h"

CPlayer::CPlayer()
{
	// Texture 로딩하기
	// m_pTexture = CResourceManager::GetInst()->LoadTexture(L"PlayerTexture", L"texture\\Plane.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(FVector2D(0.f, 12.f));
	GetCollider()->SetScale(FVector2D(20.f, 40.f));


	// Texture 로딩하기
	CTexture* pTexture = CResourceManager::GetInst()->LoadTexture(L"PlayerTexture", L"texture\\link.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN"
		, pTexture
		, FVector2D(0.f, 260.f)
		, FVector2D(60.f, 65.f)
		, FVector2D(60.f, 0.f)
		, 0.09f, 10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");

	for (int i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).Offset = FVector2D(0.f, -20.f);
	}



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

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	
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
