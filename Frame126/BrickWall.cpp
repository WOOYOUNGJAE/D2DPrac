#include "stdafx.h"
#include "BrickWall.h"

CBrickWall::CBrickWall()
{
	m_eType = BRICK_WALL;
	m_eID = OBJ_WYJ_WALL;
}

bool CBrickWall::Update()
{
	if (m_bAlive == false)
		return false;

	if (m_eType == BRICK_WALL_ROTATING)
		m_fAngle += 1.f;


	CObj_WYJ::UpdateMove();
	CObj_WYJ::UpdateWorldTransform();


	return true;
}
