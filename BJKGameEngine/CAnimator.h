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
	map<wstring, CAnimation*>	m_mapAnim;		// ��� Animation
	CAnimation*					m_pCurAnim;		// ���� ������� Animation
	CObject*					m_pOwner;		// Animator ���� ������Ʈ
	bool						m_bRepeat;		// �ݺ� ��� ����




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

