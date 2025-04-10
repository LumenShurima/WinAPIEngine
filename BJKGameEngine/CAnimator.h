#pragma once


class CObject;
class CAnimation;
class CTexture;



class CAnimator
{
public:
	CAnimator();
	CAnimator(CAnimator& _origin);
	~CAnimator();

	friend class CObject;
private:
	map<wstring, CAnimation*>	m_mapAnim;		// 모든 Animation
	CAnimation*					m_pCurAnim;		// 현재 재생중인 Animation
	CObject*					m_pOwner;		// Animator 소유 오브젝트
	bool						m_bRepeat;		// 반복 재생 여부




public:
	CObject* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, CTexture* _pTexture, FVector2D _LT, FVector2D _SliceSize, FVector2D _step,float _Length, UINT _FrameCount);
	CAnimation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);




	void update();
	void FinalUpdate();
	void render(HDC _dc);

};

