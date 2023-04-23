#pragma once
#include "Obj_WYJ.h"
class CBall_WYJ : public CObj_WYJ
{
public:
	CBall_WYJ()
	{
		m_fSpeed = 10.f;
		m_vMoveDir = { 0,-1,0 };
		D3DXVec3Normalize(&m_vMoveDir, &m_vMoveDir);
		m_eID = OBJ_WYJ_BALL;
		m_tWorld.vScale = { 30, 30,0 };
		m_tWorld.vPos = { 400,300,0 };
	}
	virtual ~CBall_WYJ() override
	{
		
	}

public:
	// getter
	// setter
	// overrides
	virtual void		Initialize(void) override;
	virtual bool		Update(void) override;
	virtual void		LateUpdate(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

	virtual void OnCollisionStay_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY) override{};
	virtual void OnCollisionEnter_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY) override{};
	virtual void OnCollisionExit_Legacy(CObj_WYJ* _pOther) override{};

	void OnCollisionStay(const D3DXVECTOR3 _vCollisionNormal, CObj_WYJ* _pOther) override;
	void OnCollisionEnter(const D3DXVECTOR3 _vCollisionNormal, CObj_WYJ* _pOther) override;
	void OnCollisionExit(const D3DXVECTOR3 _vCollisionAxis, CObj_WYJ* _pOther) override{};

	virtual void		UpdateMove() override;

};

