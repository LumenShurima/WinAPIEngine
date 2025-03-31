#pragma once

class CScene;

class CSceneManager
{
	SINGLETON(CSceneManager);

private:
	CScene* m_Scenes[(UINT)SCENE_TYPE::END];	// ¸ðµç ¾À ¸ñ·Ï
	CScene* m_pCurScene;						// ÇöÀç ¾À


public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurrentScene() { return m_pCurScene; }


private:
	void ChangeOtherScene(SCENE_TYPE _Scene);
	friend class CEventManager;
	

};

