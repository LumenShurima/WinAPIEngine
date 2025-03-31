#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}


void CAnimator::update()
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->update();
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTexture, FVector2D _LT, FVector2D _SliceSize, FVector2D _step, UINT _FrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);

	assert(nullptr != pAnim);


	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTexture, _LT, _SliceSize, _step, _FrameCount);


	m_mapAnim.insert(make_pair(_strName, pAnim));
}

CAnimation* CAnimator::FindAnimation(const wstring& _strName)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimator::Play()
{
}

