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

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}
	if (!m_pMonster)
	{
		m_pMonster = new CMonster;
		m_pMonster->Initialize();
	}

	if (!m_pTank)
	{
		m_pTank = new CTank;
		m_pTank->Initialize();
	}

	if (!m_pPlayerWYJ)
	{
		m_pPlayerWYJ = new CPlayer_WYJ;
		m_pPlayerWYJ->Initialize();
		CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_BALL, m_pBall);
	}
	if (!m_pBall)
	{
		m_pBall = new CBall_WYJ;
		m_pBall->Initialize();
		CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_BALL, m_pBall);
	}

	CObj_WYJ* pTmpObj = new CBrickWall;
	pTmpObj->Initialize();
	pTmpObj->Set_WorldPos(WINCX >> 1, 50);
	pTmpObj->Set_WorldScale(WINCX - 100, 100);
	CObjManager_WYJ::Get_Instance()->AddObject(OBJ_WYJ_WALL, pTmpObj);
	
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
