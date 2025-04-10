#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pCurAnim(nullptr)
	, m_pOwner(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::CAnimator(CAnimator& _origin)
	: m_mapAnim(_origin.m_mapAnim)
	, m_pCurAnim(_origin.m_pCurAnim)
	, m_pOwner(_origin.m_pOwner)
	, m_bRepeat(_origin.m_bRepeat)
{	
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}


void CAnimator::update()
{
	

}

void CAnimator::FinalUpdate()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->update();
		// 컴파일러 최적화에 의해서 앞에가 실패하면 뒤에는 비교 안함
		// 그리고 OR도 앞에게 성공하면 뒤는 검사 안함
		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->SetFrame(0);
		}

	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);
}

void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _pTexture
	, FVector2D _LT, FVector2D _SliceSize, FVector2D _step
	, float _Length, UINT _FrameCount)
{
	CAnimation* pAnim = FindAnimation(_strName);

	assert(nullptr == pAnim);


	pAnim = new CAnimation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTexture, _LT, _SliceSize, _step, _Length, _FrameCount);


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

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}


