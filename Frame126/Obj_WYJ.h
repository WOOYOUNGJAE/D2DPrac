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
 * \brief local 벡터모음
 */
struct LocalTransform
{
	D3DXVECTOR3 vScale{1,1,1};
	D3DXVECTOR3 vForward{0,1,0};
	D3DXVECTOR3 vPos{0,0,0};
};

/**
 * \brief World 벡터모음
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

	//setter
	virtual void Set_WorldPos(const D3DXVECTOR3& _vPos) { m_tWorld.vPos.x = _vPos.x; m_tWorld.vPos.y = _vPos.y; }
	virtual void Set_WorldPos(const float _x, const float _y)
	{ m_tWorld.vPos.x = _x; m_tWorld.vPos.y = _y; }
	virtual void Set_WorldScale(const float _x, const float _y)
	{
		m_tWorld.vScale.x = _x;
		m_tWorld.vScale.y = _y;
	}

	virtual void		Initialize(void)PURE;
	virtual bool		Update(void);
	virtual void		LateUpdate(void);
	virtual void		Render(HDC hDC);
	virtual void		Release(void)PURE;

	virtual void OnCollisionStay_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY)PURE;
	virtual void OnCollisionEnter_Legacy(CObj_WYJ* _pOther, DIR_WYJ _eDir, float _fDiffCX, float _fDiffCY)PURE;
	virtual void OnCollisionExit_Legacy(CObj_WYJ* _pOther)PURE;

	virtual void OnCollisionStay(const D3DXVECTOR3 _vCollisionNormal) PURE;
	virtual void OnCollisionEnter(const D3DXVECTOR3 _vCollisionAxis) PURE;
	virtual void OnCollisionExit(const D3DXVECTOR3 _vCollisionAxis) PURE;


	/**
	 * \brief 월드 변환
	 * \param _option 디폴트(0)면 모두변환\n
	 * 1: S만\n
	 * 2: R만\n
	 * 3: T만\n
	 * 4: SR만\n
	 * 5: RT만\n
	 * 6: ST만\n
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
	 * \brief 중점 주변의 4개 점
	 */
	D3DXVECTOR3	m_vDots[DOT_COUNT]; // 항상 좌상단부터 시계방향
	D3DXVECTOR3 m_vMoveDir;


	bool m_bAlive;
	bool m_bIsRectangle;

	float			m_fSpeed;
	/**
	 * \brief x축과 이루는 각도
	 */
	float			m_fDeltaAngle;
	/**
	 * \brief 크기 배율. 기본1
	 */
	float			m_fDeltaScale;

	// OBB Collider
	D3DXVECTOR3 m_vCollisionAxis;
	float m_fOBBWidth;
	float m_fOBBHeight;
	
};

