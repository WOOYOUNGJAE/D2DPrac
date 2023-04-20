#pragma once
#include "Obj_WYJ.h"
class CObjManager_WYJ
{
public:
	CObjManager_WYJ();
	~CObjManager_WYJ();

public:
	static CObjManager_WYJ* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjManager_WYJ;

		return m_pInstance;
	}

	static void		Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	// getter
	CObj_WYJ* Get_Player() { return m_ObjList[OBJ_WYJ_PLAYER].front(); }
	list<CObj_WYJ*>* Get_ObjList() { return m_ObjList; }

	// setter
	void Initialize();
	void Update();
	void LateUpdate();
	void Render(HDC _dc);
	void Release();

	void AddObject(OBJ_ID_WYJ _eID, CObj_WYJ* _pObj);
	
private:
	static  CObjManager_WYJ* m_pInstance;

	list<CObj_WYJ*> m_ObjList[OBJ_ID_WYJ_END];
	
};

