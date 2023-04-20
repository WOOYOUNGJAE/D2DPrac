#include "stdafx.h"
#include "Player_WYJ.h"
#include "KeyMgr.h"

CPlayer_WYJ::CPlayer_WYJ()
{
	m_fSpeed = 10.f;
	m_tWorld.vScale = { WINCX * 0.2f, WINCY * 0.05f ,0 };
	m_tWorld.vPos = { 400,500,0 };
}

CPlayer_WYJ::~CPlayer_WYJ()
{
}

void CPlayer_WYJ::Initialize()
{

}

bool CPlayer_WYJ::Update()
{
	if (m_bAlive == false)
		return false;

	Key_Input();
	CObj_WYJ::UpdateWorldTransform(6);

	return true;
}

void CPlayer_WYJ::LateUpdate()
{
}

void CPlayer_WYJ::Render(HDC hDC)
{
	CObj_WYJ::Render(hDC);
}

void CPlayer_WYJ::Release()
{
}

void CPlayer_WYJ::OnCollisionStay_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY)
{
}

void CPlayer_WYJ::OnCollisionEnter_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY)
{
}

void CPlayer_WYJ::OnCollisionExit_Legacy(CObj_WYJ* _pOther)
{
}

void CPlayer_WYJ::UpdateMove()
{
	CObj_WYJ::UpdateMove();
}

void CPlayer_WYJ::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_vMoveDir = D3DXVECTOR3(1, 0, 0);
		CObj_WYJ::UpdateMove();
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_vMoveDir = D3DXVECTOR3(-1, 0, 0);
		CObj_WYJ::UpdateMove();
	}

}
