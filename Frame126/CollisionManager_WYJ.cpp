#include "stdafx.h"
#include "CollisionManager_WYJ.h"

#include <memory>

CCollisionManager_WYJ* CCollisionManager_WYJ::m_pInstance = nullptr;

CCollisionManager_WYJ::CCollisionManager_WYJ()
{
}

CCollisionManager_WYJ::~CCollisionManager_WYJ()
{
}

void CCollisionManager_WYJ::RectCollisionStay(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src)
{
	float fDiffCX = 0;
	float fDiffCY = 0;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (CheckRect(Dst, Src, &fDiffCX, &fDiffCY))
			{
				// 상하 충돌일 때
				if (fDiffCX > fDiffCY)
				{
					// 하 충돌
					if (Dst->Get_WorldPos().y < Src->Get_WorldPos().y)
					{
						Dst->OnCollisionStay_Legacy(Src, WYJ_DOWN, fDiffCX, fDiffCY);
						Src->OnCollisionStay_Legacy(Dst, WYJ_UP, fDiffCX, fDiffCY);
					}
					else
					{
						Dst->OnCollisionStay_Legacy(Src, WYJ_UP, fDiffCX, fDiffCY);
						Src->OnCollisionStay_Legacy(Dst, WYJ_DOWN, fDiffCX, fDiffCY);
					}
				}
				else
				{
					if (Dst->Get_WorldPos().x < Src->Get_WorldPos().x) // 우충돌
					{
						Dst->OnCollisionStay_Legacy(Src, WYJ_RIGHT, fDiffCX, fDiffCY);
						Src->OnCollisionStay_Legacy(Dst, WYJ_LEFT, fDiffCX, fDiffCY);
					}
					else
					{
						Dst->OnCollisionStay_Legacy(Src, WYJ_LEFT, fDiffCX, fDiffCY);
						Src->OnCollisionStay_Legacy(Dst, WYJ_RIGHT, fDiffCX, fDiffCY);
					}
				}
			}
		}
	}
}

void CCollisionManager_WYJ::RectCollisionEnter(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src)
{
	float fDiffCX = 0;
	float fDiffCY = 0;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			//list<set<CObj*, CObj*>>::iterator iter = 
			auto iter = find(m_CollisionEnterList.begin(), m_CollisionEnterList.end(),
				pair<CObj_WYJ*, CObj_WYJ*>(Dst, Src));

			// 찾았으면, 이미 충돌했으면 리턴
			if (iter != m_CollisionEnterList.end())
				return;

			if (CheckRect(Dst, Src, &fDiffCX, &fDiffCY))
			{
				// 상하 충돌일 때
				if (fDiffCX > fDiffCY)
				{
					// 하 충돌
					if (Dst->Get_WorldPos().y < Src->Get_WorldPos().y)
					{
						Dst->OnCollisionEnter_Legacy(Src, WYJ_DOWN, fDiffCX, fDiffCY);
						Src->OnCollisionEnter_Legacy(Dst, WYJ_UP, fDiffCX, fDiffCY);
					}
					else
					{
						Dst->OnCollisionEnter_Legacy(Src, WYJ_UP, fDiffCX, fDiffCY);
						Src->OnCollisionEnter_Legacy(Dst, WYJ_DOWN, fDiffCX, fDiffCY);
					}
				}
				else
				{
					if (Dst->Get_WorldPos().x < Src->Get_WorldPos().x) // 우충돌
					{
						Dst->OnCollisionEnter_Legacy(Src, WYJ_RIGHT, fDiffCX, fDiffCY);
						Src->OnCollisionEnter_Legacy(Dst, WYJ_LEFT, fDiffCX, fDiffCY);
					}
					else
					{
						Dst->OnCollisionEnter_Legacy(Src, WYJ_LEFT, fDiffCX, fDiffCY);
						Src->OnCollisionEnter_Legacy(Dst, WYJ_RIGHT, fDiffCX, fDiffCY);
					}
				}

				m_CollisionEnterList.emplace_back(pair<CObj_WYJ*, CObj_WYJ*>(Dst, Src));
			}
		}
	}
}

void CCollisionManager_WYJ::RectCollisionExit(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src)
{
	float fDiffCX = 0;
	float fDiffCY = 0;

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			auto iter = find(m_CollisionEnterList.begin(), m_CollisionEnterList.end(),
				pair<CObj_WYJ*, CObj_WYJ*>(Dst, Src));

			// 못찾았으면,  리턴
			if (iter == m_CollisionEnterList.end())
				continue;;

			// 충돌 안했으면
			if (CheckRect(Dst, Src, &fDiffCX, &fDiffCY) == false)
			{
				Dst->OnCollisionExit_Legacy(Src);
				Src->OnCollisionExit_Legacy(Dst);

				m_CollisionEnterList.erase(iter);
			}
		}
	}
}

void CCollisionManager_WYJ::OBBCollisionStay(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src)
{

}

void CCollisionManager_WYJ::OBBCollisionEnter(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src)
{
}

void CCollisionManager_WYJ::OBBCollisionExit(list<CObj_WYJ*> _Dst, list<CObj_WYJ*> _Src)
{
}

bool CCollisionManager_WYJ::CheckRect(CObj_WYJ* _pDst, CObj_WYJ* _pSrc, float* pDiffCX, float* pDiffCY)
{
	float fWidth = fabs(_pDst->Get_WorldPos().x - _pSrc->Get_WorldPos().x);
	float fHeight = fabs(_pDst->Get_WorldPos().y - _pSrc->Get_WorldPos().y);

	float fRadiusX = (_pDst->Get_WorldScale().x + _pSrc->Get_WorldScale().x) * 0.5f;
	float fRadiusY = (_pDst->Get_WorldScale().y + _pSrc->Get_WorldScale().y) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		*pDiffCX = fRadiusX - fWidth;
		*pDiffCY = fRadiusY - fHeight;

		return  true;
	}

	return false;
}
