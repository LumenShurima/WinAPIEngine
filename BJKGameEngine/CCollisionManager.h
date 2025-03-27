#pragma once
class CCollisionManager
{
	SINGLETON(CCollisionManager);

private:
	UINT m_arrCheck[(UINT)(GROUP_TYPE::END)];


public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }


private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
};

