#include "stdafx.h"
#include "Obj_WYJ.h"

CObj_WYJ::CObj_WYJ() : m_fSpeed(0.f), m_fDeltaAngle(0.f), m_fDeltaScale(1.f),
m_eID(OBJ_ID_WYJ_END), m_bAlive(true), m_fOBBWidth(0.f), m_fOBBHeight(0.f), m_bIsRectangle(true)
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

void CObj_WYJ::LateUpdate()
{
	LateUpdateOBB();
}

void CObj_WYJ::Render(HDC hDC)
{




	()
	MoveToEx(hDC, m_vDots[0].x, m_vDots[0].y, nullptr);
	LineTo(hDC, m_vDots[1].x, m_vDots[1].y);
	LineTo(hDC, m_vDots[2].x, m_vDots[2].y);
	LineTo(hDC, m_vDots[3].x, m_vDots[3].y);
	LineTo(hDC, m_vDots[0].x, m_vDots[0].y);
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
	for (int i = 0; i < DOT_COUNT; ++i)
	{
		D3DXVec3TransformCoord(m_vDots + i, m_vDots + i,
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
	m_vDots[0] = { -0.5f, -0.5f, 0 };
	m_vDots[1] = { 0.5f, -0.5f, 0 };
	m_vDots[2] = { 0.5f, 0.5f, 0 };
	m_vDots[3] = { -0.5f, 0.5f, 0 };
}

void CObj_WYJ::LateUpdateOBB()
{
	float fCurrentMinX = m_vDots[0].x;
	float fCurrentMaxX = m_vDots[0].x;
	float fCurrentMinY = m_vDots[0].y;
	float fCurrentMaxY = m_vDots[0].y;
	for (int i = 0; i < DOT_COUNT; ++i)
	{
		if (m_vDots[i].x < fCurrentMinX)
			fCurrentMinX = m_vDots[i].x;
		else if (m_vDots[i].x > fCurrentMaxX)
			fCurrentMaxX = m_vDots[i].x;

		if (m_vDots[i].y < fCurrentMinY)
			fCurrentMinY = m_vDots[i].y;
		else if (m_vDots[i].y > fCurrentMaxY)
			fCurrentMaxY = m_vDots[i].y;
	}

	m_fOBBWidth = fabs(fCurrentMaxX - fCurrentMinX);
	m_fOBBHeight = fabs(fCurrentMaxY - fCurrentMinY);
}
