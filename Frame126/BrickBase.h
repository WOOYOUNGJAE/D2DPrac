#pragma once
#include "Obj_WYJ.h"

enum BRICK_TYPE
{
	BRICK_WALL,
	BRICK_SIMPLE, // �� �� ������ �����
	BRICK_TYPE_END,
};

/**
 * \brief ���� ���̽� Ŭ����
 */
class CBrickBase : public CObj_WYJ
{
public:
	CBrickBase();
	virtual ~CBrickBase();

public:
	// getter
	// setter
	// overrides
	virtual void		Initialize(void) override;
	virtual bool		Update(void) override;
	virtual void		LateUpdate(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

	virtual void		UpdateMove() override;


protected:
	BRICK_TYPE m_eType;
};