#pragma once



// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

// 2. 키 입력 이벤트 처리
// tap, hold, away
#define CurMousePos CKeyManager::GetInst()->GetMousePos()



enum class EKEY_STATE
{
	NONE,	// 눌리지 않고, 여전히 눌리지 않은 상태
	Started,	// 막 누른 시점
	Triggered,	// 누르고 있는
	Completed,	// 막 땐 시점
	
};

enum class EKEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LBTN,
	RBTN,


	FinalEND
};

struct FKeyInfo
{
	EKEY_STATE eState; // 키의 상태값
	bool bPressed; // 이전 프레임에서 눌렸는지 여부
};


class CKeyManager
{
	SINGLETON(CKeyManager);

private:
	vector<FKeyInfo>	m_Keys;
	FVector2D			m_CurMousePos;

public:
	void init();
	void update();

public:
	EKEY_STATE GetKeyState(EKEY _eKey) {return m_Keys[(int)_eKey].eState;}
	FVector2D GetMousePos() { return m_CurMousePos; }
};


