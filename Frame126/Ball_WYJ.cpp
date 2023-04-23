#include "stdafx.h"
#include "Ball_WYJ.h"

#include "BrickBase.h"

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
}


void CBall_WYJ::UpdateMove()
{
	CObj_WYJ::UpdateMove();
}
