#pragma once

#include "Include.h"
#include "Obj_WYJ.h"
class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);	// 데이터를 초기화하는 함수
	void		Update(void);		// 매 프레임마다 갱신하는 함수
	void		Render(void);		// 매 프레임마다 출력하는 함수
	void		Release(void);		// 객체 파괴 시 메모리 해제 함수

private:
	HDC			m_DC;
	CObj*		m_pPlayer;
	CObj*		m_pMonster;
	CObj*		m_pTank;

	CObj_WYJ* m_pPlayerWYJ;
	CObj_WYJ* m_pBall;
};

