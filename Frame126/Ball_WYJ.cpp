#include "stdafx.h"
#include "Ball_WYJ.h"

#include "BrickBase.h"

void CBall_WYJ::Initialize()
{
}

bool CBall_WYJ::Update()
{
	if (m_iBallHP <= 0)
		m_bAlive = false;

	return CObj_WYJ::Update();
}

void CBall_WYJ::LateUpdate()
{
	CObj_WYJ::LateUpdate();
}

void CBall_WYJ::Render(HDC hDC)
{
	if (m_iBallHP > 4)
	{
		MoveToEx(hDC, m_vDots[0].x, m_vDots[0].y, nullptr);
		LineTo(hDC, m_vDots[1].x, m_vDots[1].y);
		LineTo(hDC, m_vDots[2].x, m_vDots[2].y);
		LineTo(hDC, m_vDots[3].x, m_vDots[3].y);
		LineTo(hDC, m_vDots[0].x, m_vDots[0].y);		
	}
	else
	{
		HPEN hGreenPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		HPEN hOldPen = (HPEN)SelectObject(hDC, hGreenPen);;

		MoveToEx(hDC, m_vDots[0].x, m_vDots[0].y, nullptr);

		LineTo(hDC, m_vDots[1].x, m_vDots[1].y);
		LineTo(hDC, m_vDots[2].x, m_vDots[2].y);
		LineTo(hDC, m_vDots[3].x, m_vDots[3].y);
		LineTo(hDC, m_vDots[0].x, m_vDots[0].y);

		SelectObject(hDC, hOldPen); // DC에 초록색 펜 선택
		DeleteObject(hGreenPen);
	}
}

void CBall_WYJ::Release()
{
}

void CBall_WYJ::OnCollisionStay(const D3DXVECTOR3 _vCollisionNormal, CObj_WYJ* _pOther)
{
	m_tWorld.vPos -= m_vMoveDir * m_fSpeed;
	float UdotV = D3DXVec3Dot(&-m_vMoveDir, &_vCollisionNormal);
	D3DXVECTOR3 vTmp = UdotV * _vCollisionNormal * 2;
	m_vMoveDir = m_vMoveDir + UdotV * _vCollisionNormal * 2;
	//m_vMoveDir = {}

	if (_pOther->Get_ID() == OBJ_WYJ_BRICK)
	{
		dynamic_cast<CBrickBase*>(_pOther)->Set_BrickHPPlus(-1);
	}
}

void CBall_WYJ::OnCollisionEnter(const D3DXVECTOR3 _vCollisionNormal, CObj_WYJ* _pOther)
{
	m_tWorld.vPos -= m_vMoveDir * m_fSpeed;
	float UdotV = D3DXVec3Dot(&-m_vMoveDir, &_vCollisionNormal);
	D3DXVECTOR3 vTmp = UdotV * _vCollisionNormal * 2;
	m_vMoveDir = m_vMoveDir + UdotV * _vCollisionNormal * 2;

	if (_pOther->Get_ID() == OBJ_WYJ_BRICK)
	{
		//_pOther->Set_Alive(false);
	}

	--m_iBallHP;
}


void CBall_WYJ::UpdateMove()
{
	CObj_WYJ::UpdateMove();
}
