#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CTimeManager.h"
#include "CMissile.h"
#include "CScene.h"
#include "CSceneManager.h"

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

void CPlayer::CreateMissile()
{
	FVector2D MissilePos = GetPos();
	MissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;

	pMissile->SetPos(MissilePos);
	pMissile->SetScale(FVector2D(25.f, 25.f));

	CScene* pCurScene = CSceneManager::GetInst()->GetCurrentScene();
	pCurScene->AddObject(pMissile);
}
