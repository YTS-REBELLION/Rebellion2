#pragma once
#include "Script.h"
#include "Mesh.h"

struct tAnimation {
	wstring Name;
	UINT StartFrame;
	UINT EndFrame;
	bool Stop;
	bool Repeat;
};

class CSwordScript:
	public CScript
{
private:
    tAnimation* m_pCurAnimation;

    tMTAnimClip* m_pCurAnimClip;
    tMTAnimClip* m_pNextAnimClip;

    tMTBone* m_pTargetBone;
    CGameObject* m_pTargetObject;
    int m_iTargetBoneIdx;

	PERSON_OBJ_TYPE m_eType;


	// 검 좌표, 회전값...
	Vec3 vTrans;
	Vec4 qRot;
	Vec3 vRot;


	CGameObject* m_pTrail[30];
	float						m_fCurTime;			// 정점 생성 후 경과 시간
	float						m_fEmitTime;		// 정점 생성 기준 시간
	float						m_fLifeTime[30];
	int							m_iCount;

	CGameObject* m_pTrail2[30];
	float						m_fCurTime2;			// 정점 생성 후 경과 시간
	float						m_fEmitTime2;		// 정점 생성 기준 시간
	float						m_fLifeTime2[30];
	int							m_iCount2;

public:

	void init(PERSON_OBJ_TYPE type, CGameObject* _target, int _boneIdx);

	void update();

	void awake();

	void Set_Sword_To_Fbx();

	void Set_SwordTrail();

	CSwordScript();
	virtual ~CSwordScript();
	CGameObject* m_pPlayer;

public:
	CLONE(CSwordScript);

public:
	virtual void OnCollisionEnter(CCollider2D* _pOther);
	virtual void OnCollision(CCollider2D* _pOther);
	virtual void OnCollisionExit(CCollider2D* _pOther);
};