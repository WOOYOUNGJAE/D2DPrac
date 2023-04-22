#pragma once
#include "Obj_WYJ.h"

enum BRICK_TYPE
{
	BRICK_WALL,
	BRICK_SIMPLE, // 한 번 맞으면 사라짐
	BRICK_TYPE_END,
};

/**
 * \brief 벽돌 베이스 클래스
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

	void OnCollisionStay(const D3DXVECTOR3* _vCollisionAxis) override{};
	void OnCollisionEnter(const D3DXVECTOR3* _vCollisionAxis) override{};
	void OnCollisionExit(const D3DXVECTOR3* _vCollisionAxis) override{};


protected:
	BRICK_TYPE m_eType;
};