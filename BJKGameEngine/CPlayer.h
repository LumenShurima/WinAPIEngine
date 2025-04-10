#pragma once
#include "CObject.h"


class CTexture;

class CPlayer : public CObject
{
public:
	CPlayer();
	CPlayer(const CPlayer& _origin)
		: CObject(_origin)
	{}
	~CPlayer();

private:

public:
	virtual void update();
	virtual void render(HDC _dc);
	void CreateMissile();

private:

	CLONE(CPlayer)

};

