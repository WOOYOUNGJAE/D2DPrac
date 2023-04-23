#pragma once
#include "Obj_WYJ.h"

enum BRICK_TYPE
{
	BRICK_WALL,
	BRICK_WALL_ROTATING,
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
	void Set_BrickType(BRICK_TYPE _eType) { m_eType = _eType; }
	void Set_BrickHP(int _iHP) { m_iBrickHP = _iHP; }
	void Set_BrickHPPlus(int _iAdding) { m_iBrickHP += _iAdding; }

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

	void OnCollisionStay(const D3DXVECTOR3 _vCollisionNormal, CObj_WYJ* _pOther) override{};
	void OnCollisionEnter(const D3DXVECTOR3 _vCollisionNormal, CObj_WYJ* _pOther) override{};
	void OnCollisionExit(const D3DXVECTOR3 _vCollisionAxis, CObj_WYJ* _pOther) override{};


protected:
	BRICK_TYPE m_eType;
	int m_iBrickHP;
};