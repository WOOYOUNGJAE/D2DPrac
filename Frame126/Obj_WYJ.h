#pragma once
#include "Include.h"

#define DOT_COUNT 4

enum OBJ_ID_WYJ
{
	OBJ_WYJ_PLAYER,
	OBJ_WYJ_WALL,
	OBJ_WYJ_BRICK,
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

	virtual const float Get_Angle() { return m_fAngle; }
	const bool Get_IsRectangle() { return m_bIsRectangle; }

	virtual const float Get_OBBWidth() { return m_fOBBWidth; }
	virtual const float Get_OBBHeight() { return m_fOBBHeight; }

	virtual OBJ_ID_WYJ Get_ID() { return m_eID; }
	//setter
	virtual void Set_WorldPos(const D3DXVECTOR3& _vPos) { m_tWorld.vPos.x = _vPos.x; m_tWorld.vPos.y = _vPos.y; }
	virtual void Set_WorldPos(const float _x, const float _y)
	{ m_tWorld.vPos.x = _x; m_tWorld.vPos.y = _y; }
	virtual void Set_WorldScale(const float _x, const float _y)
	{
		m_tWorld.vScale.x = _x;
		m_tWorld.vScale.y = _y;
	}
	virtual void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	virtual void Set_Alive(bool _b) { m_bAlive = _b; }
	virtual void Set_MoveDir(const D3DXVECTOR3& _vDir)
	{
		m_vMoveDir.x = _vDir.x; m_vMoveDir.y = _vDir.y; m_vMoveDir.z = 0;
		D3DXVec3Normalize(&m_vMoveDir, &m_vMoveDir);
	}
	virtual void Set_MoveDir(const float _x, const float _y)
	{
		m_vMoveDir.x = _x; m_vMoveDir.y = _y; m_vMoveDir.z = 0;
		D3DXVec3Normalize(&m_vMoveDir, &m_vMoveDir);
	}
	virtual void		Initialize(void)PURE;
	virtual bool		Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void)PURE;

	virtual void OnCollisionStay_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY)PURE;
	virtual void OnCollisionEnter_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY)PURE;
	virtual void OnCollisionExit_Legacy(CObj_WYJ* _pOther)PURE;

	virtual void OnCollisionStay(const D3DXVECTOR3 _vCollisionNormal, CObj_WYJ* _pOther) PURE;
	virtual void OnCollisionEnter(const D3DXVECTOR3 _vCollisionNormal, CObj_WYJ* _pOther) PURE;
	virtual void OnCollisionExit(const D3DXVECTOR3 _vCollisionAxis, CObj_WYJ* _pOther) PURE;


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
	float			m_fAngle;
	/**
	 * \brief ũ�� ����. �⺻1
	 */
	float			m_fDeltaScale;

	// OBB Collider
	D3DXVECTOR3 m_vCollisionAxis;
	float m_fOBBWidth;
	float m_fOBBHeight;
	
};

