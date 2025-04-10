#include "pch.h"
#include "CScene_Start.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CTexture.h"
#include "CPathManager.h"
#include "CCollisionManager.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CCamera.h"
#include "CUI.h"
#include "CBtnUI.h"
#include "CPanelUI.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();

	if (KEY_Started(EKEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_Started(EKEY::LBTN))
	{
		FVector2D LookAt = CCamera::GetInst()->GetRealPos(CurMousePos);
		CCamera::GetInst()->SetLookAt(LookAt);
	}
	
}

void CScene_Start::Enter()
{
	// Object �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(FVector2D(640.f,384.f));
	pObj->SetScale(FVector2D(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);


	// CCamera::GetInst()->SetTarget(pObj);

	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(FVector2D(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/
	

	// ���� ��ġ
	UINT Count = 10;
	float MoveDist = 25.f;
	float ObjectScale = 50.f;
	FVector2D wndResolution = CCore::GetInst()->GetResolution();
	float Term = (wndResolution.x - ((MoveDist + ObjectScale / 2.f) * 2)) / (float)(Count-1);
	CMonster* pMonsterObj = nullptr;

	for (UINT i = 0; i < Count; ++i)
	{
		// ���� �߰�
		pMonsterObj = new CMonster;
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(FVector2D((MoveDist + ObjectScale / 2.f) + (float)i * Term, 50.f));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(MoveDist);
		pMonsterObj->SetScale(FVector2D(ObjectScale, ObjectScale));
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	CUI* pPanelUI = new CPanelUI;
	FVector2D Resolution = CCore::GetInst()->GetResolution();
	pPanelUI->SetName(L"MainUI");
	pPanelUI->SetScale(FVector2D(500.f, 300.f));
	pPanelUI->SetPos(FVector2D(Resolution.x - pPanelUI->GetScale().x, 0.f));


	CUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUi");
	pBtnUI->SetScale(FVector2D(100.f, 40.f));
	pBtnUI->SetPos(FVector2D(0.f, 0.f));

	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);


	((CBtnUI*)pBtnUI)->BindMouseLbtnClicked([pObj]() { ((CPlayer*)pObj)->CreateMissile(); });
	// Ÿ�� �ε�
	// LoadFile("");


	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹üũ
	CCollisionManager::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionManager::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJECTILE_PLAYER);

	//  Camera Look ����
	CCamera::GetInst()->SetLookAt(wndResolution / 2.f);

}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionManager::GetInst()->Reset();
}
