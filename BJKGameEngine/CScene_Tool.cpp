#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyManager.h"


CScene_Tool::CScene_Tool()
{

}

CScene_Tool::~CScene_Tool()
{

}

void CScene_Tool::update()
{
	CScene::update();

	if (KEY_Started(EKEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Tool::Enter()
{

}

void CScene_Tool::Exit()
{

}
