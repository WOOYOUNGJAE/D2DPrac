#include "stdafx.h"
#include "Player_WYJ.h"
#include "KeyMgr.h"
#include "Ball_WYJ.h"
#include "ObjManager_WYJ.h"

CPlayer_WYJ::CPlayer_WYJ() : m_fPosinAngle(270), m_fPosinLength(100.f)
{
	m_fSpeed = 20.f;
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

	// Posin
	D3DXMatrixIdentity(&m_tMats.matWorld);
	D3DXMatrixTranslation(
		&m_tMats.matTranslation, // 변환 행렬
		m_tWorld.vPos.x,
		m_tWorld.vPos.y ,
		0);
	D3DXMatrixRotationZ(&m_tMats.matRotation, D3DXToRadian(m_fPosinAngle));

	vFirePos = { 0,-m_fPosinLength,0 };
	
	D3DXVec3TransformCoord(&vFirePos, &vFirePos, &m_tMats.matRotation);
	D3DXVec3TransformCoord(&vFirePos, &vFirePos, &m_tMats.matTranslation);
	
	return true;
}

void CPlayer_WYJ::LateUpdate()
{
}

void CPlayer_WYJ::Render(HDC hDC)
{
	CObj_WYJ::Render(hDC);

	MoveToEx(hDC, m_tWorld.vPos.x, m_tWorld.vPos.y, nullptr);
	LineTo(hDC, vFirePos.x, vFirePos.y);
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

	if (CKeyMgr::Get_Instance()->Key_Pressing('E'))
	{
		m_fPosinAngle += 1.f;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing('Q'))
	{
		m_fPosinAngle -= 1.f;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		
		CObj_WYJ* pBall = new CBall_WYJ;
		pBall->Initialize();
		pBall->Set_WorldPos(vFirePos);
		D3DXVECTOR3 vLocalFireDir = vFirePos - m_tWorld.vPos;
		D3DXVec3Normalize(&vLocalFireDir, &vLocalFireDir);
		pBall->Set_MoveDir(vLocalFireDir);
		CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_BALL, pBall);
	}

}
