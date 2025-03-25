#include "pch.h"
#include "CMissile.h"
#include "CTimeManager.h"

CMissile::CMissile()
	: m_Theta{ 3.f*  PI / 2.f}
{

}

CMissile::~CMissile()
{

}

void CMissile::update()
{
	FVector2D Pos = GetPos();

	Pos.x += 600.f * cosf(m_Theta) * DeltaTime;
	Pos.y -= 600.f * sinf(m_Theta) * DeltaTime;

	SetPos(Pos);
}

void CMissile::render(HDC _dc)
{
	FVector2D Pos = GetPos();
	FVector2D Scale = GetScale();

	Ellipse(_dc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f)
		, (int)(Pos.x + Scale.x / 2.f), (int)(Pos.y + Scale.y / 2.f));
}
