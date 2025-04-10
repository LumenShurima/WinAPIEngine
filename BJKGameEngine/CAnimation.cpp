#include "pch.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CCamera.h"


CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTexture(nullptr)
	, m_CurFrame(0)
	, m_Time(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}



void CAnimation::Create(CTexture* _pTexture, FVector2D _LT, FVector2D _SliceSize, FVector2D _step, float _Length, UINT _FrameCount)
{
	m_pTexture = _pTexture;


	FAnimFrame frm = {};
	for (UINT i = 0; i < _FrameCount; ++i)
	{
		frm.Length = _Length;
		frm.Slice = _SliceSize;
		frm.LT = _LT + _step * (float)(i); 

		m_Frames.push_back(frm);
	}
}

void CAnimation::update()
{

	if (m_bFinish)
		return;
	m_Time += DeltaTime;
	float Length = m_Frames[m_CurFrame].Length;

	if (m_Time > Length)
	{
		++m_CurFrame;

		if (m_Frames.size() <= m_CurFrame)
		{
			m_CurFrame = -1;
			m_bFinish = true;
		}

		m_Time -= Length;
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;


	

	CObject* pObj = m_pAnimator->GetObj();
	FVector2D Pos = pObj->GetPos();


	FVector2D Slice =  m_Frames[m_CurFrame].Slice;
	FVector2D LT = m_Frames[m_CurFrame].LT;
	Pos += m_Frames[m_CurFrame].Offset;

	Pos = CCamera::GetInst()->GetRenderPos(Pos);

	TransparentBlt(_dc
	, (int)(Pos.x - Slice.x / 2.f)
	, (int)(Pos.y - Slice.y / 2.f)
	, (int)(Slice.x)
	, (int)(Slice.y)
	, m_pTexture->GetDC()
	, (int)(LT.x)
	, (int)(LT.y)
	, (int)(Slice.x)
	, (int)(Slice.y)
	, RGB(255, 0, 255));
}
