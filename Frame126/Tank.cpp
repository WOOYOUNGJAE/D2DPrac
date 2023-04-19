#include "stdafx.h"
#include "Tank.h"

CTank::CTank() : m_fPosinAngle(0.f), m_fBodyAngle(0.f),
m_fBodyRadius(60.f), m_fPosinLength(120.f)
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
	vNewPos = m_tInfo.vPos;

	vBodyDots[0] = D3DXVECTOR3(
		vNewPos.x - m_fBodyRadius * 0.5f,
		vNewPos.y - m_fBodyRadius * 0.5f, 0);

	vBodyDots[1] = D3DXVECTOR3(
		vNewPos.x + m_fBodyRadius * 0.5f,
		vNewPos.y - m_fBodyRadius * 0.5f,
		0
	);
	vBodyDots[2] = D3DXVECTOR3(
		vNewPos.x - m_fBodyRadius * 0.5f,
		vNewPos.y + m_fBodyRadius * 0.5f,
		0
	);
	vBodyDots[3] = D3DXVECTOR3(
		vNewPos.x + m_fBodyRadius * 0.5f,
		vNewPos.y + m_fBodyRadius * 0.5f,
		0
	);
}

void CTank::Update()
{
	Key_Input();

	//UpdatePos();
	UpdateRotation();
	//UpdateBodyDots(); // UpdateRect
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
+	LineTo(hDC, (int)vBodyDots[0].x,
		(int)vBodyDots[0].y);

	MoveToEx(hDC, (int)m_tInfo.vPos.x, (int)m_tInfo.vPos.y, nullptr);
	LineTo(hDC, (int)vPosinDot.x, (int)vPosinDot.y);
}

void CTank::Release()
{
}

void CTank::UpdateRotation()
{
#pragma region Body
 	//m_fBodyAngle += 1.f;
	m_fBodyAngle += D3DXToRadian(1);

	// z축 회전 변환 행렬
	D3DXMatrixTranslation(&matTranslation, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);
	D3DXMatrixRotationZ(&matRotation, m_fBodyAngle);

	vBodyDots[0] = { -m_fBodyRadius, -m_fBodyRadius,0 };
	vBodyDots[1] = { m_fBodyRadius, -m_fBodyRadius ,0 };
	vBodyDots[2] = { -m_fBodyRadius, +m_fBodyRadius,0 };
	vBodyDots[3] = { +m_fBodyRadius, +m_fBodyRadius,0 };

	matFinal = matTranslation * matRotation;

	// 3차원 행렬을 4차원으로
	D3DXVec3TransformCoord(vBodyDots, vBodyDots, &matRotation);
	D3DXVec3TransformCoord(vBodyDots + 1, vBodyDots + 1, &matRotation);
	D3DXVec3TransformCoord(vBodyDots + 2, vBodyDots + 2, &matRotation);
	D3DXVec3TransformCoord(vBodyDots + 3, vBodyDots + 3, &matRotation);
	
	D3DXVec3TransformCoord(vBodyDots, vBodyDots, &matTranslation);
	D3DXVec3TransformCoord(vBodyDots + 1, vBodyDots + 1, &matTranslation);
	D3DXVec3TransformCoord(vBodyDots + 2, vBodyDots + 2, &matTranslation);
	D3DXVec3TransformCoord(vBodyDots + 3, vBodyDots + 3, &matTranslation);
#pragma endregion Body

#pragma region Posin
	m_fPosinAngle += D3DXToRadian(-1);
	D3DXMatrixTranslation(&matTranslation, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);
	D3DXMatrixRotationZ(&matRotation, m_fPosinAngle);

	vPosinDot = { m_fPosinLength, 0, 0 };
	D3DXVec3TransformCoord(&vPosinDot, &vPosinDot, &matRotation);
	D3DXVec3TransformCoord(&vPosinDot, &vPosinDot, &matTranslation);

#pragma endregion Posin


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
		vNewPos.x - m_fBodyRadius * 0.5f,
		vNewPos.y - m_fBodyRadius * 0.5f, 0);

	vBodyDots[1] = D3DXVECTOR3(
		vNewPos.x + m_fBodyRadius * 0.5f,
		vNewPos.y - m_fBodyRadius * 0.5f,
		0
		);
	vBodyDots[2] = D3DXVECTOR3(
		vNewPos.x - m_fBodyRadius * 0.5f,
		vNewPos.y + m_fBodyRadius * 0.5f,
		0
		);
	vBodyDots[3] = D3DXVECTOR3(
		vNewPos.x + m_fBodyRadius * 0.5f,
		vNewPos.y + m_fBodyRadius * 0.5f,
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
