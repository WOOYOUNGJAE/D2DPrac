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

	void OnCollisionStay_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY) override{}
	void OnCollisionEnter_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY) override{}
	void OnCollisionExit_Legacy(CObj_WYJ* _pOther) override{}

	void OnCollisionStay() override{};
	void OnCollisionEnter() override{};
	void OnCollisionExit() override{};


protected:
	BRICK_TYPE m_eType;
};