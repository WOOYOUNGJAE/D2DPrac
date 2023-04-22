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
				continue;

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
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			int iDotCount = 0;
			const D3DXVECTOR3* pTmpDots = Dst->Get_Dots(&iDotCount);
			D3DXVECTOR3 vLine{};
			D3DXVECTOR3 vCollisionAxis{};

			// 01
			vLine = pTmpDots[1] - pTmpDots[0];
			D3DXVec3Normalize(&vLine, &vLine);
			if (SAT_Exist(vLine, Dst, Src))
				continue;
			// 32
			vLine = pTmpDots[2] - pTmpDots[1];
			D3DXVec3Normalize(&vLine, &vLine);
			if (SAT_Exist(vLine, Dst, Src))
				continue;

			pTmpDots = Src->Get_Dots(&iDotCount);
			// 01
			vLine = pTmpDots[1] - pTmpDots[0];
			D3DXVec3Normalize(&vLine, &vLine);
			if (SAT_Exist(vLine, Src, Dst))
				continue;
			// 32
			vLine = pTmpDots[2] - pTmpDots[1];
			D3DXVec3Normalize(&vLine, &vLine);
			if (SAT_Exist(vLine, Src, Dst))
				continue;

			// 충돌 감지 순간
			// 1. Src의 중점과 가장 가까운 Dst의 꼭지점을 찾는다. -> 충돌 선분의 한 점, 이하 vNearest
			// 2.Src의 중점으로부터 vNearest의 양 옆의 점에 선을 그어서
			//	Dst의 네 선분과 교차점이 몇개인지 구한다.
			// 3. 세 직선 중, 교차점이 단 한가지(교차점이 한가지이면 그 교차점은 Dst의 꼭지점)인 직선이 충돌 면()

			D3DXVECTOR3 vDstCenter = Dst->Get_WorldPos();
			D3DXVECTOR3 vSrcCenter = Src->Get_WorldPos();
			D3DXVECTOR3 vNearest = pTmpDots[0];
			D3DXVECTOR3 vPotential0{};
			D3DXVECTOR3 vPotential1{};
			D3DXVECTOR3 vRealCollided{};
			D3DXVECTOR3 vCollidedNormal{};

			float fNearestDistance = D3DXVec3Length(&(pTmpDots[0] - vDstCenter));
			for (int i = 1; i < 4; ++i)
			{
				float fCurrentDistance = D3DXVec3Length(&(pTmpDots[i] - vDstCenter));
				if (fCurrentDistance < fNearestDistance)
				{
					fNearestDistance = fCurrentDistance;
					vNearest = pTmpDots[i];
					switch (i)
					{
					case 0:
						vPotential0 = pTmpDots[3];
						vPotential1 = pTmpDots[1];
						break;
					case 1:
						vPotential0 = pTmpDots[0];
						vPotential1 = pTmpDots[2];
						break;
					case 2:
						vPotential0 = pTmpDots[1];
						vPotential1 = pTmpDots[3];
						break;
					case 3:
						vPotential0 = pTmpDots[2];
						vPotential1 = pTmpDots[0];
						break;

					default:
						break;
					}
				}
			}

			// two lines
			float m0 = (vPotential0.y - vNearest.y) / (vPotential0.x - vNearest.x);
			float b0 = vNearest.y - m0 * vNearest.x;

			float m1 = (vPotential1.y - vNearest.y) / (vPotential1.x - vNearest.x);
			float b1 = vNearest.y - m1 * vNearest.x;

			float mCenterToDot = (vPotential0.y - vDstCenter.x) / (vPotential0.x - vDstCenter.x);
			float bCenterToDot = vDstCenter.y - mCenterToDot * vDstCenter.x;

			// potential 0
			// 두 x범위 사이의 해의 개수 구하기
			if ((vNearest.x * mCenterToDot + bCenterToDot - vNearest.y) *
				(vPotential0.x * mCenterToDot + bCenterToDot - vPotential0.y)
				< 0
				) // 두 점 사이에 교차점이 있다.
			{
				vRealCollided = vPotential0 - vNearest;
				D3DXVECTOR3 vMiddle = (vPotential0 + vNearest) * 0.5f;
				vCollidedNormal = vMiddle - vSrcCenter;
				D3DXVec3Normalize(&vCollidedNormal, &vCollidedNormal);
			}

			// potential1
			mCenterToDot = (vPotential1.y - vDstCenter.x) / (vPotential1.x - vDstCenter.x);
			bCenterToDot = vDstCenter.y - mCenterToDot * vDstCenter.x;

			if ((vNearest.x * mCenterToDot + bCenterToDot - vNearest.y) *
				(vPotential1.x * mCenterToDot + bCenterToDot - vPotential1.y)
				< 0
				) // 두 점 사이에 교차점이 있다.
			{
				vRealCollided = vPotential1 - vNearest;
				D3DXVECTOR3 vMiddle = (vPotential1 + vNearest) * 0.5f;
				vCollidedNormal = vMiddle - vSrcCenter;
				D3DXVec3Normalize(&vCollidedNormal, &vCollidedNormal);
			}

			Src->OnCollisionStay(vCollidedNormal);
			Dst->OnCollisionStay(vCollidedNormal);
			continue;

		}
	}
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

bool CCollisionManager_WYJ::CheckRect(CObj_WYJ* _pDst, CObj_WYJ* _pSrc)
{
	float fWidth = fabs(_pDst->Get_WorldPos().x - _pSrc->Get_WorldPos().x);
	float fHeight = fabs(_pDst->Get_WorldPos().y - _pSrc->Get_WorldPos().y);

	float fRadiusX = (_pDst->Get_OBBWidth() + _pSrc->Get_OBBWidth()) * 0.5f;
	float fRadiusY = (_pDst->Get_OBBHeight() + _pSrc->Get_OBBHeight()) * 0.5f;

	if ((fRadiusX >= fWidth) && (fRadiusY >= fHeight))
	{
		return  true;
	}

	return false;
}

bool CCollisionManager_WYJ::SAT_Exist(const D3DXVECTOR3& _vAxis, CObj_WYJ* _pDst, CObj_WYJ* _pSrc)
{
	float fDstLength = 0.f;
	float fSrcLength = 0.f;
	float fDistance = 0.f;
	int iDotCount = 0; // not used
	const D3DXVECTOR3* pTmpDots = _pDst->Get_Dots(&iDotCount);
	D3DXVECTOR3 vCenterToExtent{};
	D3DXVECTOR3 vProjected{};
	const D3DXVECTOR3 DstCenter = _pDst->Get_WorldPos();
	const D3DXVECTOR3 SrcCenter = _pSrc->Get_WorldPos();


	D3DXVECTOR3 vCenterToCenter = DstCenter - SrcCenter;

	vProjected = 
	 MyProjection(vCenterToCenter, _vAxis);

	fDistance = D3DXVec3Length(&vProjected);

	// Dst Center to Dot0
	vCenterToExtent = pTmpDots[0] - DstCenter;
	vProjected = MyProjection(vCenterToExtent, _vAxis);
	fDstLength = D3DXVec3Length(&vProjected);
	// Dst Center to Dot1
	vCenterToExtent = pTmpDots[1] - DstCenter;
	vProjected = MyProjection(vCenterToExtent, _vAxis);
	if (D3DXVec3Length(&vProjected) > fDstLength)
		fDstLength = D3DXVec3Length(&vProjected);


	pTmpDots = _pSrc->Get_Dots(&iDotCount);
	// Src Center to Src0
	vCenterToExtent = pTmpDots[0] - SrcCenter;
	vProjected = MyProjection(vCenterToExtent, _vAxis);
	fSrcLength = D3DXVec3Length(&vProjected);
	// Src Center to Dot1
	vCenterToExtent = pTmpDots[1] - SrcCenter;
	vProjected = MyProjection(vCenterToExtent, _vAxis);
	if (D3DXVec3Length(&vProjected) > fSrcLength)
		fSrcLength = D3DXVec3Length(&vProjected);


	return fDistance > fDstLength + fSrcLength;
}

D3DXVECTOR3 CCollisionManager_WYJ::MyProjection(const D3DXVECTOR3 U, const D3DXVECTOR3 V)
{
	// v' = (u * v) * v
	float UdotV = D3DXVec3Dot(&U, &V);
	D3DXVECTOR3 result = UdotV * V;
	return result;
}
