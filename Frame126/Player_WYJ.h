#pragma once
#include "Obj_WYJ.h"
class CPlayer_WYJ : public CObj_WYJ
{
public:
	CPlayer_WYJ();
	virtual ~CPlayer_WYJ() override;
	
public:
	// getter
	// setter
	// overrides
	virtual void		Initialize(void) override;
	virtual bool		Update(void) override;
	virtual void		LateUpdate(void) override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release(void) override;

	virtual void OnCollisionStay_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY) override;
	virtual void OnCollisionEnter_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY) override;
	virtual void OnCollisionExit_Legacy(CObj_WYJ* _pOther) override;

	virtual void OnCollisionStay(const D3DXVECTOR3 _vCollisionNormal) override {};
	virtual void OnCollisionEnter(const D3DXVECTOR3 _vCollisionAxis) override {};
	virtual void OnCollisionExit(const D3DXVECTOR3 _vCollisionAxis) override {};

	virtual void		UpdateMove() override;


	// originals
	void Key_Input();
};
