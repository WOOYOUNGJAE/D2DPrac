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
	CObj_WYJ::Render(hDC);
}

void CBrickBase::Release()
{
}

void CBrickBase::UpdateMove()
{
	CObj_WYJ::UpdateMove();
}
