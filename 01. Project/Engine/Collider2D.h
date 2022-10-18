#pragma once
#include "Component.h"

#include "Ptr.h"
#include "Mesh.h"
#include "Material.h"

class CCollider2D :
	public CComponent
{
private:
	static			UINT  g_iColID;

private:
	Vec3			m_vOffsetPos;
	Vec3			m_vOffsetScale;
	Vec3			m_vOffsetRot;

	COLLIDER2D_TYPE m_eType;
	int				m_iCollisionCount;	// �浹 Ƚ��
		
	Ptr<CMesh>      m_pColMesh;			// �浹ü�� �׸��� ���� Mesh
	Ptr<CMaterial>	m_pColMtrl;			// �浹ü�� �׸��� ���� Material

	Matrix			m_matColWorld;		// �浹ü ���� ���

	UINT			m_iColID;			// �浹ü ���� ID ��
	
	BoundingBox		m_bBB;
	COL_PLANE		m_ePlane;
	//BoundingSphere	m_bBS;

	bool			m_bActive;
public:
	virtual void update();
	virtual void finalupdate();
	void render();

	void SetActive(bool _Type) { m_bActive = _Type; }
	bool GetActvie() { return m_bActive; }

	void OnCollisionEnter(CCollider2D* _pOther); // �浹ü�� ó�� �浹
	void OnCollision(CCollider2D* _pOther);      // �浹 ��
	void OnCollisionExit(CCollider2D* _pOther);  // �浹ü�� ���� ������ ��

public:
	void SetOffsetPos(const Vec3& _vPos) { m_vOffsetPos = _vPos; }
	void SetOffsetScale(const Vec3& _vScale) { m_vOffsetScale = _vScale; }
	void SetOffsetRot(const Vec3& _vRot) { m_vOffsetRot = _vRot; }

	const Vec3& GetOffsetPos() { return m_vOffsetPos; }
	const Vec3& GetOffsetScale() { return m_vOffsetScale; }
	COLLIDER2D_TYPE GetColliderType() { return m_eType;}

	void SetColliderType(COLLIDER2D_TYPE _eType);
	void SetColliderType(COLLIDER2D_TYPE _eType, wstring _str);
	void SetFBXColliderType(wstring _str);

	UINT GetColID() { return m_iColID; }
	COL_PLANE GetPlane() { return m_ePlane; }
	void SetPlane(COL_PLANE _eType) { m_ePlane = _eType; }
	const Matrix& GetColliderWorldMat() { return m_matColWorld; }

public:
	BoundingBox GetBB() { return m_bBB; }
	//BoundingSphere GetBS() { return m_bBS; }

	void SetBB(BoundingBox box, float Radius = 1.f) { m_bBB = box; }
	//void SetBS(BoundingSphere sphere) { m_bBS = sphere; m_bBS.Center.y += m_bBS.Radius;}
	//void SetCenter(Vec3 Center_pos) { m_bBS.Center = Center_pos; }

public:
	CLONE(CCollider2D);
	virtual void SaveToScene(FILE* _pFile);
	virtual void LoadFromScene(FILE* _pFile);

public:
	void operator = (const CCollider2D& _other);

public:
	CCollider2D();
	CCollider2D(const CCollider2D& _other);
	virtual ~CCollider2D();
};
