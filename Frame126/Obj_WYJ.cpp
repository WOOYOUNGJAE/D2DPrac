#include "stdafx.h"
#include "Obj_WYJ.h"

CObj_WYJ::CObj_WYJ() : m_fSpeed(0.f), m_fDeltaAngle(0.f), m_fDeltaScale(1.f),
m_eID(OBJ_ID_WYJ_END), m_bAlive(true)
{
	D3DXMatrixIdentity(&m_tMats.matWorld);
	D3DXMatrixIdentity(&m_tMats.matScale);
	D3DXMatrixIdentity(&m_tMats.matRotation);
	D3DXMatrixIdentity(&m_tMats.matTranslation);


	m_tWorld.vScale = { 1,1,0 };
	m_tWorld.vForward = { 0,1,0 };
	m_tWorld.vPos = { WINCX >> 1,WINCY >> 1,0 };
	
	m_vMoveDir = { 0,0,0 };
	ResetDotsPos();
}

CObj_WYJ::~CObj_WYJ()
{
}

bool CObj_WYJ::Update()
{
	if (m_bAlive == false)
		return false;

	// prototype
	// update data

	UpdateMove();
	UpdateWorldTransform();

	return true; // alive
}

void CObj_WYJ::Render(HDC hDC)
{
	MoveToEx(hDC, m_vRectDots[0].x, m_vRectDots[0].y, nullptr);
	LineTo(hDC, m_vRectDots[1].x, m_vRectDots[1].y);
	LineTo(hDC, m_vRectDots[3].x, m_vRectDots[3].y);
	LineTo(hDC, m_vRectDots[2].x, m_vRectDots[2].y);
	LineTo(hDC, m_vRectDots[0].x, m_vRectDots[0].y);
}

void CObj_WYJ::UpdateWorldTransform(int _option)
{
	// 최종 변환행렬을 항등행렬로 초기화
	D3DXMatrixIdentity(&m_tMats.matWorld);

	switch (_option)
	{
	case 0:
		UpdateWorldScale();
		UpdateWorldRotation();
		UpdateWorldTranslation();
		break;
	case 1:
		UpdateWorldScale();
		break;
	case 2:
		UpdateWorldRotation();
		break;
	case 3:
		UpdateWorldTranslation();
		break;
	case 4:
		UpdateWorldScale();
		UpdateWorldRotation();
		break;
	case 5:
		UpdateWorldRotation();
		UpdateWorldTranslation();
		break;
	case 6:
		UpdateWorldScale();
		UpdateWorldTranslation();
		break;		
	}
	
	ResetDotsPos();
	// 4개의 점 이동
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(m_vRectDots + i, m_vRectDots + i,
			&m_tMats.matWorld);
	}
}

void CObj_WYJ::UpdateWorldScale()
{
	D3DXMatrixScaling(&m_tMats.matScale,
		m_tWorld.vScale.x,
		m_tWorld.vScale.y, 
		1);

	m_tMats.matWorld *= m_tMats.matScale;
}

void CObj_WYJ::UpdateWorldRotation()
{
	D3DXMatrixRotationZ(&m_tMats.matRotation, m_fDeltaAngle);

	m_tMats.matWorld *= m_tMats.matRotation;
}

void CObj_WYJ::UpdateWorldTranslation()
{
	D3DXMatrixTranslation(
		&m_tMats.matTranslation, // 변환 행렬
		m_tWorld.vPos.x,
		m_tWorld.vPos.y,
		0);

	m_tMats.matWorld *= m_tMats.matTranslation;
}

void CObj_WYJ::UpdateMove()
{
	// update dir
	m_tWorld.vPos += m_vMoveDir * m_fSpeed;
}

void CObj_WYJ::ResetDotsPos()
{
	m_vRectDots[0] = { -0.5f, -0.5f, 0 };
	m_vRectDots[1] = { 0.5f, -0.5f, 0 };
	m_vRectDots[2] = { -0.5f, 0.5f, 0 };
	m_vRectDots[3] = { 0.5f, 0.5f, 0 };
}
