#include "pch.h"
#include "CTimeManager.h"
#include "CCore.h"

CTimeManager::CTimeManager()
	: m_llCurCount{}
	, m_llFrequency{}
	, m_llPrevCount{}
	, m_deltaTime(0.)
	, m_CallCount(0)
	, m_Accumulator(0)
	, m_FPS(0)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_llPrevCount);
	
	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_llFrequency);


}

void CTimeManager::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_deltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)(m_llFrequency.QuadPart);
	
	// 이전 카운트 값을 현재값으로 갱신(다음번에 계산을 위해서)
	
	m_llPrevCount = m_llCurCount;

	++m_CallCount;

	m_Accumulator += m_deltaTime;

	if (m_Accumulator >= 1.)
	{
		m_FPS = m_CallCount;
		m_Accumulator = 0.;
		m_CallCount = 0;

		WCHAR szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DeltaTime : %f", m_FPS, m_deltaTime);
		SetWindowText(CCore::GetInst()->getMainHwnd(), szBuffer);
	}
}
