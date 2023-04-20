#include "stdafx.h"
#include "BrickBase.h"

CBrickBase::CBrickBase() : m_eType(BRICK_TYPE_END)
{
}

CBrickBase::~CBrickBase()
{
}

void CBrickBase::Initialize()
{
}

bool CBrickBase::Update()
{
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
