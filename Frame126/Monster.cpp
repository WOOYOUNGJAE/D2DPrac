#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize(void)
{
	m_tInfo.vPos = { 100.f, 100.f, 0.f };	

	m_fSpeed = 2.f;
}

void CMonster::Update(void)
{
	m_tInfo.vDir = m_pTarget->Get_Info().vPos - m_tInfo.vPos;
	// 벡터의 정규화 과정

	float	fLength = sqrtf(m_tInfo.vDir.x * m_tInfo.vDir.x + m_tInfo.vDir.y * m_tInfo.vDir.y);

	m_tInfo.vDir.x /= fLength;
	m_tInfo.vDir.y /= fLength;
	m_tInfo.vDir.z = 0.f;

	D3DXVECTOR3 vTmpVector = { 1,0,0 };
	
	//float fDot = D3DXVec3Dot(&vTmpVector, &m_tInfo.vDir); // cos()
	float fDot = D3DXVec3Dot(&m_tInfo.vDir, &vTmpVector); // cos(1,0 과 플레이어 향한 벡터간 각도)

	float fAngle = acosf(fDot); // 
	if (m_tInfo.vPos.y < m_pTarget->Get_Info().vPos.y)
		fAngle *= -1.f;
	


	m_tInfo.vPos.x += cosf(fAngle) * 3.f;
	m_tInfo.vPos.y -= sin(fAngle) * 3.f;
	
}

void CMonster::Render(HDC hDC)
{
	Ellipse(hDC,
		int(m_tInfo.vPos.x - 50.f),
		int(m_tInfo.vPos.y - 50.f),
		int(m_tInfo.vPos.x + 50.f),
		int(m_tInfo.vPos.y + 50.f));
}

void CMonster::Release(void)
{
}
