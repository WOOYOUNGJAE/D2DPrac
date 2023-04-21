#pragma once
#include "Include.h"

#define DOT_COUNT 4

enum OBJ_ID_WYJ
{
	OBJ_WYJ_PLAYER,
	OBJ_WYJ_WALL,
	OBJ_WYJ_BALL,
	OBJ_ID_WYJ_END,
};

struct TransformMats
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
};

/**
 * \brief local ���͸���
 */
struct LocalTransform
{
	D3DXVECTOR3 vScale{1,1,1};
	D3DXVECTOR3 vForward{0,1,0};
	D3DXVECTOR3 vPos{0,0,0};
};

/**
 * \brief World ���͸���
 */
struct WorldTransform
{
	D3DXVECTOR3 vScale;
	D3DXVECTOR3 vForward;
	D3DXVECTOR3 vPos;
};

class CObj_WYJ abstract
{
public:
	CObj_WYJ();
	virtual ~CObj_WYJ();

public:
	// getter
	virtual const D3DXVECTOR3 Get_LocalScale() { return m_tLocal.vScale; }
	virtual const D3DXVECTOR3 Get_LocalForward() { return m_tLocal.vForward; }
	virtual const D3DXVECTOR3 Get_LocalPos() { return m_tLocal.vPos; }
	
	virtual const D3DXVECTOR3 Get_WorldScale() { return m_tWorld.vScale; }
	virtual const D3DXVECTOR3 Get_WorldForward() { return m_tWorld.vForward; }
	virtual const D3DXVECTOR3 Get_WorldPos() { return m_tWorld.vPos; }
	
	virtual const D3DXVECTOR3 Get_MoveDir() { return m_vMoveDir; }

	virtual const D3DXVECTOR3* Get_Dots(int* _pDotCount) { return m_vDots; }

	const bool Get_IsRectangle() { return m_bIsRectangle; }

	virtual const float Get_OBBWidth() { return m_fOBBWidth; }
	virtual const float Get_OBBHeight() { return m_fOBBHeight; }
public:
	virtual void		Initialize(void)PURE;
	virtual bool		Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void)PURE;

	virtual void OnCollisionStay_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY)PURE;
	virtual void OnCollisionEnter_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY)PURE;
	virtual void OnCollisionExit_Legacy(CObj_WYJ* _pOther)PURE;

	virtual void OnCollisionStay() PURE;
	virtual void OnCollisionEnter() PURE;
	virtual void OnCollisionExit() PURE;


	/**
	 * \brief ���� ��ȯ
	 * \param _option ����Ʈ(0)�� ��κ�ȯ\n
	 * 1: S��\n
	 * 2: R��\n
	 * 3: T��\n
	 * 4: SR��\n
	 * 5: RT��\n
	 * 6: ST��\n
	 */
	virtual void		UpdateWorldTransform(int _option = 0);
	virtual void		UpdateWorldScale();
	virtual void		UpdateWorldRotation();
	virtual void		UpdateWorldTranslation();

	virtual void UpdateMove();
	void		ResetDotsPos();

	void LateUpdateOBB();
protected:	
	OBJ_ID_WYJ m_eID;

	TransformMats	m_tMats;
	LocalTransform m_tLocal;
	WorldTransform m_tWorld;

	/**
	 * \brief ���� �ֺ��� 4�� ��
	 */
	D3DXVECTOR3	m_vDots[DOT_COUNT]; // �׻� �»�ܺ��� �ð����
	D3DXVECTOR3 m_vMoveDir;


	bool m_bAlive;
	bool m_bIsRectangle;

	float			m_fSpeed;
	/**
	 * \brief x��� �̷�� ����
	 */
	float			m_fDeltaAngle;
	/**
	 * \brief ũ�� ����. �⺻1
	 */
	float			m_fDeltaScale;

	// OBB Collider
	float m_fOBBWidth;
	float m_fOBBHeight;
};

