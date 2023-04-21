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
				// ���� �浹�� ��
				if (fDiffCX > fDiffCY)
				{
					// �� �浹
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
					if (Dst->Get_WorldPos().x < Src->Get_WorldPos().x) // ���浹
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

			// ã������, �̹� �浹������ ����
			if (iter != m_CollisionEnterList.end())
				return;

			if (CheckRect(Dst, Src, &fDiffCX, &fDiffCY))
			{
				// ���� �浹�� ��
				if (fDiffCX > fDiffCY)
				{
					// �� �浹
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
					if (Dst->Get_WorldPos().x < Src->Get_WorldPos().x) // ���浹
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

			// ��ã������,  ����
			if (iter == m_CollisionEnterList.end())
				continue;;

			// �浹 ��������
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
			if (CheckRect(Dst, Src))
			{
				// OBB Collision Check
				int iDotCount = 0;
				const D3DXVECTOR3* pTmpDots = Dst->Get_Dots(&iDotCount);
				D3DXVECTOR3 vLine{};

				// 01
				vLine = pTmpDots[1] - pTmpDots[0];
				vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
				if (SAT_Exist(vLine, Dst, Src))
					continue;
				// 32
				vLine = pTmpDots[2] - pTmpDots[3];
				vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
				if (SAT_Exist(vLine, Dst, Src))
					continue;

				pTmpDots = Src->Get_Dots(&iDotCount);
				// 01
				vLine = pTmpDots[1] - pTmpDots[0];
				vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
				if (SAT_Exist(vLine, Src, Dst))
					continue;
				// 32
				vLine = pTmpDots[2] - pTmpDots[3];
				vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
				if (SAT_Exist(vLine, Src, Dst))
					continue;

				if (Dst->Get_IsRectangle())
				{
					// �� �� ���簢���̸�
					if (Src->Get_IsRectangle())
					{
						Src->OnCollisionStay();
						Dst->OnCollisionStay();
						continue;
					}
					else // Dst�� ���簢���̸�
					{
						// 03
						vLine = pTmpDots[3] - pTmpDots[0];
						vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
						if (SAT_Exist(vLine, Src, Dst))
							continue;
						// 12
						vLine = pTmpDots[2] - pTmpDots[1];
						vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
						if (SAT_Exist(vLine, Src, Dst))
							continue;
					}
				}
				else if (Src->Get_IsRectangle()) // Src�� ���簢���̸�
				{
					// Dst �߰��˻�

					pTmpDots = Dst->Get_Dots(&iDotCount);
					// 03
					vLine = pTmpDots[3] - pTmpDots[0];
					vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
					if (SAT_Exist(vLine, Dst, Src))
						continue;
					// 12
					vLine = pTmpDots[2] - pTmpDots[1];
					vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
					if (SAT_Exist(vLine, Dst, Src))
						continue;
				}
				else // �� �� ���簢���� �ƴ϶��
				{
					// Dst �߰��˻�
					pTmpDots = Dst->Get_Dots(&iDotCount);
					// 03
					vLine = pTmpDots[3] - pTmpDots[0];
					vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
					if (SAT_Exist(vLine, Dst, Src))
						continue;
					// 12
					vLine = pTmpDots[2] - pTmpDots[1];
					vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
					if (SAT_Exist(vLine, Dst, Src))
						continue;

					// Src �߰��˻�
					pTmpDots = Src->Get_Dots(&iDotCount);
					// 03
					vLine = pTmpDots[3] - pTmpDots[0];
					vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
					if (SAT_Exist(vLine, Src, Dst))
						continue;
					// 12
					vLine = pTmpDots[2] - pTmpDots[1];
					vLine = D3DXVECTOR3(-vLine.y, vLine.x, 0);
					if (SAT_Exist(vLine, Src, Dst))
						continue;
				}


				// �� ����ϸ�
				Src->OnCollisionStay();
				Dst->OnCollisionStay();
			}
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

bool CCollisionManager_WYJ::SAT_Exist(const D3DXVECTOR3& _vNormal, CObj_WYJ* _pDst, CObj_WYJ* _pSrc)
{

}
