#pragma once
#include "CObject.h"


class CTexture;

class CPlayer : public CObject
{
public:
	CPlayer();
	CPlayer(const CPlayer& _origin)
		: CObject(_origin)
		, m_pTexture(_origin.m_pTexture)
	{}
	~CPlayer();

private:
	CTexture* m_pTexture;

public:
	virtual void update();
	virtual void render(HDC _dc);

private:
	void CreateMissile();

	CLONE(CPlayer)

};

