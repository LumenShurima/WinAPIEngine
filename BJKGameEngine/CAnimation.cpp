#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::Create(CTexture* _pTexture, FVector2D _LT, FVector2D _SliceSize, FVector2D _step, UINT _FrameCount)
{

}

void CAnimation::update()
{
}

void CAnimation::render(HDC _dc)
{
}
