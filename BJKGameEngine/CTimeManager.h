#pragma once

#define DeltaTime CTimeManager::GetInst()->GetDeltaTime()
#define ExactDeltaTime CTimeManager::GetInst()->GetExactDeltaTime()


class CTimeManager
{
	SINGLETON(CTimeManager);
private:
	LARGE_INTEGER m_llCurCount;
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llFrequency;

	double m_deltaTime;
	double m_Accumulator;
	UINT m_CallCount;
	UINT m_FPS;

public:
	void init();
	void update();
	void render();


public:
	double GetExactDeltaTime() { return m_deltaTime; }
	float GetDeltaTime() { return (float)m_deltaTime; }
};

