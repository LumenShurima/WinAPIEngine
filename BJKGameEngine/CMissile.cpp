#include "pch.h"
#include "CMissile.h"
#include "CTimeManager.h"

CMissile::CMissile()
	: m_Theta{ PI }
	, m_Dir(FVector2D(1.f, 1.f))
{
	m_Dir.Normalize();
	CreateCollider();
}

CMissile::~CMissile()
{

}

void CMissile::update()
{
	FVector2D Pos = GetPos();

	// Pos.x += 600.f * cosf(m_Theta) * DeltaTime;
	// Pos.y -= 600.f * sinf(m_Theta) * DeltaTime;

	Pos.x += 600.f * m_Dir.x * DeltaTime;
	Pos.y += 600.f * m_Dir.y * DeltaTime;
	SetPos(Pos);
}

void CMissile::render(HDC _dc)
{
	FVector2D Pos = GetPos();
	FVector2D Scale = GetScale();

	Ellipse(_dc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f)
		, (int)(Pos.x + Scale.x / 2.f), (int)(Pos.y + Scale.y / 2.f));
}
