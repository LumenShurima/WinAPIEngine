#pragma once
#include "CObject.h"


class CTexture;

class CPlayer : public CObject
{
public:
	CPlayer();
	~CPlayer();

private:
	CTexture* m_pTexture;

public:
	virtual void update();
	virtual void render(HDC _dc);

private:
	void CreateMissile();

};

