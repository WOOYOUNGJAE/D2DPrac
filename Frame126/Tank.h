#pragma once
#include "Obj.h"
class CTank : public CObj
{
public:
	CTank();
	virtual ~CTank();

public:
	virtual void Initialize(void) override;
	virtual void Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void UpdateRotation();
	void UpdatePos();
	void UpdateBodyDots();
	
private:
	void		Key_Input(void);

	D3DXVECTOR3 vBodyDots[4];
	float m_fPosinAngle;
	float m_fBodyAngle;
	float m_fWidth;

	D3DXMATRIX matWorld;
	D3DXMATRIX matFinal;
	D3DXMATRIX matTranslation;
	D3DXMATRIX matRotation;

	D3DXVECTOR3 vToFour;
	D3DXMATRIX matToFour;
};

