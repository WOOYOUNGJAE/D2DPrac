#pragma once

#include "Include.h"

class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO&		Get_Info(void) const { return m_tInfo; }

public:
	virtual void		Initialize(void)PURE;
	virtual void		Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;


protected:
	INFO			m_tInfo;

	float			m_fSpeed;
};

