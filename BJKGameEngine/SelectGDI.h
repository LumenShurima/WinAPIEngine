#pragma once


class SelectGDI
{
public:
	SelectGDI(HDC _dc, PEN_TYPE _ePenType);
	SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	~SelectGDI();

private:
	HDC m_hDc;
	HPEN m_hDefaultPen;
	HBRUSH m_hDefaultBrush;
};

