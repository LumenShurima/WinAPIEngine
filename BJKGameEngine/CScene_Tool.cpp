#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyManager.h"
#include "CTile.h"
#include "CCore.h"
#include "CResourceManager.h"
#include "resource.h"
#include "CSceneManager.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIManager.h"
#include "CPathManager.h"

CScene_Tool::CScene_Tool()
	: m_RememberUI(nullptr)
{

}

CScene_Tool::~CScene_Tool()
{


}

void CScene_Tool::Enter()
{
	

	// 타일 생성
	CreateTile(5,5);

	// UI 띄우기
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

	// 2번 째 UI

	CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(FVector2D(Resolution.x - pPanelUI->GetScale().x, 0.f));
	
	((CBtnUI*)pClonePanel->GetChildUI()[0])->BindMouseLbtnClicked([this]() { SaveTileData(); });

	AddObject(pClonePanel, GROUP_TYPE::UI);


	FVector2D wndResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(wndResolution / 2.f);

	m_RememberUI = pPanelUI;
}

void CScene_Tool::Exit()
{
	DeleteAll();
}


void CScene_Tool::update()
{
	CScene::update();
	
	if (KEY_Started(EKEY::LSHIFT))
	{
		// CUIManager::GetInst()->SetFocusedUI(m_RememberUI);
		SaveTileData();
		
	}
	if (KEY_Started(EKEY::CTRL))
	{
		LoadTileData();
	}
	if (KEY_Started(EKEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
	SetTileIndex();
}

void CScene_Tool::SetTileIndex()
{
	if (KEY_Started(EKEY::LBTN))
	{
		FVector2D MousePos = CurMousePos;
		MousePos = CCamera::GetInst()->GetRealPos(MousePos);
		
		int TileX = (int)GetTileX();
		int TileY = (int)GetTileY();

		int Col = (int)MousePos.x / TILE_SIZE;
		int Row = (int)MousePos.y / TILE_SIZE;

		if (MousePos.x < 0 || TileX <= Col
			|| MousePos.y < 0 || TileY <= Row)
		{
			return;
		}


		

		UINT Index = Row * TileX + Col;
		const vector<CObject*>& Tiles = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)(Tiles[Index]))->AddIndex();


	}
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	
	// Modal
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}

}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{

	// File은 커널 오브젝트
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");
	assert(pFile);

	// 데이터 저장

	// 타일 가로세로 길이.
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);


	// 모든 타일의 개별적인 데이터 저장
	const vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}


	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathManager::GetInst()->GetContentPath();
	strTileFolder += L"tile";

	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	// Modal
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathManager::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
}



// Tile Count Window Proc
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT XCount= GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);
			UINT YCount= GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);

			CScene* CurScene = CSceneManager::GetInst()->GetCurrentScene();
			CurScene = dynamic_cast<CScene_Tool*>(CurScene);
			assert(CurScene);

			CurScene->DeleteGroup(GROUP_TYPE::TILE);
			CurScene->CreateTile(XCount, YCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
