#include "stdafx.h"
#include "Tank.h"

CTank::CTank() : m_fPosinAngle(0.f), m_fBodyAngle(0.f),
m_fWidth(90.f)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matFinal);
}
CTank::~CTank()
{
}

void CTank::Initialize()
{
	m_tInfo.vPos = D3DXVECTOR3(WINCX >> 1, WINCY >> 1, 0);
}

void CTank::Update()
{
	Key_Input();

	UpdatePos();

	UpdateBodyDots(); // UpdateRect
}

void CTank::Render(HDC hDC)
{
	MoveToEx(hDC, (int)vBodyDots[0].x,
		(int)vBodyDots[0].y, nullptr);

	LineTo(hDC, (int)vBodyDots[1].x,
		(int)vBodyDots[1].y);
	LineTo(hDC, (int)vBodyDots[3].x,
		(int)vBodyDots[3].y);
	LineTo(hDC, (int)vBodyDots[2].x,
		(int)vBodyDots[2].y);
	LineTo(hDC, (int)vBodyDots[0].x,
		(int)vBodyDots[0].y);
}

void CTank::Release()
{
}

void CTank::UpdateRotation()
{
	m_fBodyAngle += 1.f;
	m_fBodyAngle = D3DXToRadian(m_fBodyAngle);

	D3DXMatrixIdentity(&matRotation);
	// z축 회전
	D3DXMatrixRotationZ(&matRotation, m_fBodyAngle);
	matFinal *= matRotation;

	// 3차원 행렬을 4차원으로
	D3DXVec3TransformCoord(&vToFour, &m_tInfo.vPos, &matToFour);

	

}

void CTank::UpdatePos()
{
	D3DXVec3TransformCoord(&vToFour, &m_tInfo.vPos, &matToFour);
	D3DXMatrixTranslation(&matTranslation, m_tInfo.vPos.x,
		m_tInfo.vPos.y, m_tInfo.vPos.z);

	
	matWorld = matTranslation * matToFour;



}

void CTank::UpdateBodyDots()
{
	// left top right bottom
	vBodyDots[0] = D3DXVECTOR3(
		m_tInfo.vPos.x - m_fWidth * 0.5f,
		m_tInfo.vPos.y - m_fWidth * 0.5f, 0);

	vBodyDots[1] = D3DXVECTOR3(
		m_tInfo.vPos.x + m_fWidth * 0.5f,
		m_tInfo.vPos.y - m_fWidth * 0.5f,
		0
		);
	vBodyDots[2] = D3DXVECTOR3(
		m_tInfo.vPos.x - m_fWidth * 0.5f,
		m_tInfo.vPos.y + m_fWidth * 0.5f,
		0
		);
	vBodyDots[3] = D3DXVECTOR3(
		m_tInfo.vPos.x + m_fWidth * 0.5f,
		m_tInfo.vPos.y + m_fWidth * 0.5f,
		0
		);
}

void CTank::Key_Input()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.vDir = D3DXVECTOR3(-1, 0, 0);
		m_tInfo.vPos += m_tInfo.vDir;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.vDir = D3DXVECTOR3(1, 0, 0);
		m_tInfo.vPos += m_tInfo.vDir;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.vDir = D3DXVECTOR3(0, -1, 0);
		m_tInfo.vPos += m_tInfo.vDir;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.vDir = D3DXVECTOR3(0, 1, 0);
		m_tInfo.vPos += m_tInfo.vDir;
	}
}
