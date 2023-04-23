#include "stdafx.h"
#include "BrickBase.h"

CBrickBase::CBrickBase() : m_eType(BRICK_TYPE_END), m_iBrickHP(5)
{
	m_eID = OBJ_WYJ_BRICK;
	m_eType = BRICK_SIMPLE;
}

CBrickBase::~CBrickBase()
{
}

void CBrickBase::Initialize()
{
}

bool CBrickBase::Update()
{
	if (m_eType == BRICK_SIMPLE && m_iBrickHP <= 0)
		m_bAlive = false;

	if (m_bAlive == false)
		return false;

	CObj_WYJ::Update();

	return true;
}

void CBrickBase::LateUpdate()
{
}

void CBrickBase::Render(HDC hDC)
{

	if (m_eType != BRICK_SIMPLE)
		CObj_WYJ::Render(hDC);
	else
	{
		HPEN hGreenPen;
		HPEN hOldPen;
		if (m_iBrickHP >= 3)
		{
			hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0)); // ÃÊ·Ï»ö Ææ °´Ã¼ »ý¼º
			hOldPen = (HPEN)SelectObject(hDC, hGreenPen);			
		}
		else
		{
			hGreenPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 
			hOldPen = (HPEN)SelectObject(hDC, hGreenPen);
		}


		MoveToEx(hDC, m_vDots[0].x, m_vDots[0].y, nullptr);

		LineTo(hDC, m_vDots[1].x, m_vDots[1].y);
		LineTo(hDC, m_vDots[2].x, m_vDots[2].y);
		LineTo(hDC, m_vDots[3].x, m_vDots[3].y);
		LineTo(hDC, m_vDots[0].x, m_vDots[0].y);

		SelectObject(hDC, hOldPen); // DC¿¡ ÃÊ·Ï»ö Ææ ¼±ÅÃ
		DeleteObject(hGreenPen);
	}
}

void CBrickBase::Release()
{
}

void CBrickBase::UpdateMove()
{
	CObj_WYJ::UpdateMove();
}
