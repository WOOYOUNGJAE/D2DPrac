#pragma once

#include "Include.h"

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);	// �����͸� �ʱ�ȭ�ϴ� �Լ�
	void		Update(void);		// �� �����Ӹ��� �����ϴ� �Լ�
	void		Render(void);		// �� �����Ӹ��� ����ϴ� �Լ�
	void		Release(void);		// ��ü �ı� �� �޸� ���� �Լ�

private:
	HDC			m_DC;
	CObj*		m_pPlayer;
	CObj*		m_pMonster;
	CObj*		m_pTank;
};

