#pragma once



// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������.

// 2. Ű �Է� �̺�Ʈ ó��
// tap, hold, away
#define CurMousePos CKeyManager::GetInst()->GetMousePos()



enum class EKEY_STATE
{
	NONE,	// ������ �ʰ�, ������ ������ ���� ����
	Started,	// �� ���� ����
	Triggered,	// ������ �ִ�
	Completed,	// �� �� ����
	
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
	EKEY_STATE eState; // Ű�� ���°�
	bool bPressed; // ���� �����ӿ��� ���ȴ��� ����
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


