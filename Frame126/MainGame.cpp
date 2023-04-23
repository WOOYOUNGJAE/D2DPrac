#include "stdafx.h"
#include "MainGame.h"

#include "Ball_WYJ.h"
#include "BrickWall.h"
#include "Player.h"
#include "Monster.h"
#include "ObjManager_WYJ.h"
#include "Tank.h"
#include "Player_WYJ.h"
CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_pMonster(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);
	
	if (!m_pPlayerWYJ)
	{
		m_pPlayerWYJ = new CPlayer_WYJ;
		m_pPlayerWYJ->Initialize();
		CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_PLAYER, m_pPlayerWYJ);
	}
	/*if (!m_pBall)
	{
		m_pBall = new CBall_WYJ;
		m_pBall->Initialize();
		CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_BALL, m_pBall);
	}*/

	// À°°¢Çü
	float fIntervalBetwCeil = 50.f;
	float fHexagonWidth = WINCX * 0.35f;
	float fHexagonCenterPosX = WINCX >> 1;
	const float fRootThree = 1.7320f;
	D3DXVECTOR3 vHexagonDots[5];
	vHexagonDots[0] = { fHexagonCenterPosX + 0.75f * WINCX * 0.4f,
		fRootThree * WINCX * 0.4f * 0.25f + fIntervalBetwCeil, 0 };
	vHexagonDots[1] = { fHexagonCenterPosX, fIntervalBetwCeil, 0 };
	vHexagonDots[2] = { fHexagonCenterPosX - 0.75f * WINCX * 0.4f,
		fRootThree * WINCX * 0.4f * 0.25f + fIntervalBetwCeil, 0 };
	vHexagonDots[3] = { fHexagonCenterPosX - 0.75f * WINCX * 0.4f,
	vHexagonDots[0].y + 0.5f * fRootThree * WINCX * 0.4f, 0 };
	vHexagonDots[4] = { fHexagonCenterPosX + 0.75f * WINCX * 0.4f, vHexagonDots[3].y, 0 };
	
	float fHexagonWallHeight = 20.f;
	CObj_WYJ* pHexagonWall = nullptr;
	for (int i = 0; i < 5; ++i)
	{
		pHexagonWall = new CBrickWall;
		pHexagonWall->Initialize();
		pHexagonWall->Set_WorldScale(fHexagonWidth, fHexagonWallHeight);
		pHexagonWall->Set_WorldPos(vHexagonDots[i]);
		switch (i)
		{
		case 0:
			//pHexagonWall->Set_Angle(120.f);
			pHexagonWall->Set_Angle(60);
			//dynamic_cast<CBrickBase*>(pHexagonWall)->Set_BrickType(BRICK_WALL_ROTATING);
			break;
		case 1:
			pHexagonWall->Set_Angle(180.f);
			break;
		case 2:
			pHexagonWall->Set_Angle(120.f);
			break;
		case 3:
			pHexagonWall->Set_Angle(60.f);
			break;
		case 4:
			pHexagonWall->Set_Angle(120.f);
			break;
		}
		CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_WALL, pHexagonWall);
	}
	/*pHexagonWall = new CBrickWall;
	pHexagonWall->Initialize();
	pHexagonWall->Set_WorldScale(fHexagonWidth, fHexagonWallHeight);
	pHexagonWall->Set_WorldPos(vHexagonDots[1].x, WINCY -100);
	CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_WALL, pHexagonWall);*/



	// left Wall
	CObj_WYJ* pTmpObj = new CBrickWall;
	pTmpObj->Initialize();
	pTmpObj->Set_WorldScale(WINCX, WINCY * 0.02f);
	pTmpObj->Set_WorldPos(10,
		WINCY >> 1);
	pTmpObj->Set_Angle(270.f);
	CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_WALL, pTmpObj);
	// right wall
	pTmpObj = new CBrickWall;
	pTmpObj->Initialize();
	pTmpObj->Set_WorldScale(WINCX, WINCY * 0.02f);
	pTmpObj->Set_WorldPos(WINCX - 10,
		WINCY >> 1);
	pTmpObj->Set_Angle(90.f);
	CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_WALL, pTmpObj);

	// upper wall
	pTmpObj = new CBrickWall;
	pTmpObj->Initialize();
	pTmpObj->Set_WorldScale(WINCX, WINCY * 0.02f);
	pTmpObj->Set_WorldPos(WINCX >> 1, pTmpObj->Get_WorldScale().y * 0.5f);
	pTmpObj->Set_Angle(180.f);
	CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_WALL, pTmpObj);

	//// down wall (temp
	//pTmpObj = new CBrickWall;
	//pTmpObj->Initialize();
	//pTmpObj->Set_WorldScale(WINCX, WINCY * 0.02f);
	//pTmpObj->Set_WorldPos(WINCX >> 1, WINCY - pTmpObj->Get_WorldScale().y * 0.5f);
	//CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_WALL, pTmpObj);


	// Bricks
	CObj_WYJ* pTmpBrick = nullptr;
	D3DXVECTOR3 vCreatePos{ 280, 200, 0 };

	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			pTmpBrick = new CBrickBase;
			pTmpBrick->Set_WorldScale(50.f, 20.f);
			D3DXVECTOR3 vTmpPos = { vCreatePos.x + j * pTmpBrick->Get_WorldScale().x , vCreatePos.y + i * pTmpBrick->Get_WorldScale().y , 0 };
			pTmpBrick->Set_WorldPos(vTmpPos);
			CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_BRICK, pTmpBrick);
		}
	}
}

void CMainGame::Update(void)
{
	//m_pPlayer->Update();
	//m_pMonster->Update();
	//m_pTank->Update();

	//m_pPlayerWYJ->Update();
	CObjManager_WYJ::Get_Instance()->Update();
	CObjManager_WYJ::Get_Instance()->LateUpdate();
}

void CMainGame::Render(void)
{
	Rectangle(m_DC, 0, 0, WINCX, WINCY);
	
	//m_pPlayer->Render(m_DC);
	//m_pMonster->Render(m_DC);
	//m_pTank->Render(m_DC);
	//m_pPlayerWYJ->Render(m_DC);
	CObjManager_WYJ::Get_Instance()->Render(m_DC);
}

void CMainGame::Release(void)
{
	Safe_Delete<CObj*>(m_pMonster);
	Safe_Delete<CObj*>(m_pPlayer);
	ReleaseDC(g_hWnd, m_DC);
}
