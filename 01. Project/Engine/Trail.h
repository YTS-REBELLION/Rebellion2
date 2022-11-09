#pragma once
#include "Ptr.h"
#include "Material.h"
#include "Mesh.h"

class CTrail
{
private:
	Vec3					m_vPos;
	Vec3					m_vColor;
	float					m_fWidth;

	float					m_fCurTime;				// ���� ���� �� ��� �ð�
	float					m_fLifeTime;			// ���� ���� �ð�

	bool					m_bEndPoint;			// ���� ���� ����

public:
	void init(Ptr<CTexture> _pTexture);

	virtual void update();
	virtual void finalUpdate();
	virtual void render();

	void SetColor(Vec4 _vColor) { m_vColor = _vColor; }
	void SetWidth(float _fWidth) { m_fWidth = _fWidth; }
	void SetLifeTime(float _fLifeTime) { m_fLifeTime = _fLifeTime; }

public:
	CTrail();
	virtual ~CTrail();

	CLONE(CTrail);
};