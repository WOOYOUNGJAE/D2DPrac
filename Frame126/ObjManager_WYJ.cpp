#include "stdafx.h"
#include "ObjManager_WYJ.h"
#include "CollisionManager_WYJ.h"


CObjManager_WYJ* CObjManager_WYJ::m_pInstance = nullptr;

CObjManager_WYJ::CObjManager_WYJ()
{
}

CObjManager_WYJ::~CObjManager_WYJ()
{
}

void CObjManager_WYJ::Initialize()
{
}

void CObjManager_WYJ::Update()
{
	bool bResultAlive = true;
	for (int i = 0; i < OBJ_ID_WYJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			bResultAlive = (*iter)->Update();

			if (bResultAlive == false)
			{
				Safe_Delete<CObj_WYJ*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CObjManager_WYJ::LateUpdate()
{
	for (int i = 0; i < OBJ_ID_WYJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->LateUpdate();
		}
	}

	CCollisionManager_WYJ::Get_Instance()->OBBCollisionStay(m_ObjList[OBJ_WYJ_BALL], m_ObjList[OBJ_WYJ_WALL]); 
	
}	

void CObjManager_WYJ::Render(HDC _dc)
{
	for (int i = 0; i < OBJ_ID_WYJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Render(_dc);
		}
	}
}

void CObjManager_WYJ::Release()
{
}

void CObjManager_WYJ::AddObject(OBJ_ID_WYJ _eID, CObj_WYJ* _pObj)
{
	if (_eID >= OBJ_ID_WYJ_END || _pObj == nullptr)
		return;

	m_ObjList[_eID].push_back(_pObj);
}
