#include "stdafx.h"
#include "Ball_WYJ.h"

void CBall_WYJ::Initialize()
{
}

bool CBall_WYJ::Update()
{
	return CObj_WYJ::Update();
}

void CBall_WYJ::LateUpdate()
{
	CObj_WYJ::LateUpdate();
}

void CBall_WYJ::Render(HDC hDC)
{
	CObj_WYJ::Render(hDC);
}

void CBall_WYJ::Release()
{
}

void CBall_WYJ::OnCollisionStay(const D3DXVECTOR3* _vCollisionAxis)
{
	m_tWorld.vPos -= m_vMoveDir * m_fSpeed;
	m_vMoveDir *= -1;
}

void CBall_WYJ::UpdateMove()
{
	CObj_WYJ::UpdateMove();
}
