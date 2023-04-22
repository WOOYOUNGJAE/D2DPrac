#pragma once
#include "Obj_WYJ.h"

class CCollisionManager_WYJ
{
private:
	CCollisionManager_WYJ();
	~CCollisionManager_WYJ();

public:
	static CCollisionManager_WYJ* Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CCollisionManager_WYJ;

		return m_pInstance;
	}
	void	Destroy_Instance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	void RectCollisionStay(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src);
	void RectCollisionEnter(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src);
	void RectCollisionExit(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src);

	void OBBCollisionStay(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src);
	void OBBCollisionEnter(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src);
	void OBBCollisionExit(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src);

	bool CheckRect(CObj_WYJ* _pDst, CObj_WYJ* _pSrc, float* pDiffCX, float* pDiffCY);
	bool CheckRect(CObj_WYJ* _pDst, CObj_WYJ* _pSrc);

	bool SAT_Exist(const D3DXVECTOR3& _vAxis, CObj_WYJ* _pDst, CObj_WYJ* _pSrc);
	D3DXVECTOR3 MyProjection(const D3DXVECTOR3 U, const D3DXVECTOR3 V);
private:
	static CCollisionManager_WYJ* m_pInstance;
	list<pair<CObj_WYJ*, CObj_WYJ*>> m_CollisionEnterList;

};

