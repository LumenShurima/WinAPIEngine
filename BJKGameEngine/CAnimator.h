#pragma once


class CObject;
class CAnimation;
class CTexture;



class CAnimator
{
public:
	CAnimator();
	~CAnimator();

	friend class CObject;
private:
	map<wstring, CAnimation*>	m_mapAnim;		// 모든 Animation
	CAnimation*					m_pCurAnim;		// 현재 재생중인 Animation
	CObject*					m_pOwner;		// Animator 소유 오브젝트




public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTexture, FVector2D _LT, FVector2D _SliceSize, FVector2D _step, UINT _FrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play();

	void update();
	void render(HDC _dc);

};

