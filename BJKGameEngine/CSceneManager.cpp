#include "pch.h"
#include "CSceneManager.h"

#include "CScene_Start.h"

CSceneManager::CSceneManager()
	: m_Scenes{}
	, m_pCurScene(nullptr)
{

}


CSceneManager::~CSceneManager()
{
	// �� ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_Scenes[i])
		{
			delete m_Scenes[i];
		}

	}
}

void CSceneManager::init()
{
	// Scene ����
	m_Scenes[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_Scenes[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	// m_Scenes[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	// m_Scenes[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	// m_Scenes[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;


	// ���� �� ����
	m_pCurScene = m_Scenes[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void CSceneManager::update()
{
	m_pCurScene->update();
}

void CSceneManager::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}
