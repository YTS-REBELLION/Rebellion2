#include "stdafx.h"
#include "SwordScript.h"
#include "MeshRender.h"
#include "Animator3D.h"
#include "Collider2D.h"
#include "TrailRenderer.h"

#include "PlayerScript.h"

CSwordScript::CSwordScript()
	: CScript((UINT)SCRIPT_TYPE::SWORDSCRIPT)
	, m_pTargetBone (nullptr)
	, m_fEmitTime(0.1f)
	, m_iCount(0)
{
}

CSwordScript::~CSwordScript()
{
}

void CSwordScript::init(PERSON_OBJ_TYPE type, CGameObject* _target, int _boneIdx)
{
	m_eType = type;
	m_pTargetObject = _target;
	m_iTargetBoneIdx = _boneIdx;
}

void CSwordScript::awake()
{
	// 트레일
	//m_pTrail = new CGameObject;
	//m_pTrail->SetName(L"SwordTrail");
	//m_pTrail->AddComponent(new CTransform);
	//m_pTrail->AddComponent(new CMeshRender);
	//m_pTrail->AddComponent(new CTrailRenderer);
	//m_pTrail->TrailRenderer()->init(CResMgr::GetInst()->FindRes<CTexture>(L"Sparks"));
	//m_pTrail->TrailRenderer()->SetColor(Vec4(0.8f, 0.f, 0.f, 0.1f));	// 레드 0.8f, 0.f, 0.f, 0.1f // 블루 0.f, 0.f, 0.8f, 0.1f
	//m_pTrail->TrailRenderer()->SetMaxWidth(10.f);
	//m_pTrail->TrailRenderer()->SetMinWidth(10.f);
	//m_pTrail->TrailRenderer()->SetEmit(false);
	//m_pTrail->SetActive(true);
	//m_pTrail->FrustumCheck(false);
	//m_pTrail->MeshRender()->SetDynamicShadow(false);
	////Vec3 vTrailPos = Vec3(0.f, 0.f, 0.f) - GetObj()->Transform()->GetWorldDir(DIR_TYPE::UP) * 100.f;
	////m_pTrail->Transform()->SetLocalPos(vTrailPos);
	//m_pTrail->TrailRenderer()->SetTargetObj(GetObj());
	//CSceneMgr::GetInst()->GetCurScene()->AddGameObject(L"Default", m_pTrail, false);
	////pCurScene->FindLayer(L"Default")->AddGameObject(m_pTrail);

	//if (m_pTargetObject->GetScript<CPlayerScript>()->GetMain()) {

	Ptr<CTexture> pColor = CResMgr::GetInst()->Load<CTexture>(L"Wp_trail", L"Texture\\Trail_tex.jpg");


		for (int i = 0; i < 30; i++) {
			m_pTrail[i] = new CGameObject;
			m_pTrail[i]->SetName(L"WeapeonTrail");
			m_pTrail[i]->AddComponent(new CTransform);
			m_pTrail[i]->AddComponent(new CMeshRender);
			m_pTrail[i]->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"WSphereMesh"));
			m_pTrail[i]->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"WeapeonMtrl"));
			m_pTrail[i]->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pColor.GetPointer());
			m_pTrail[i]->SetActive(false);
			m_pTrail[i]->FrustumCheck(false);
			m_pTrail[i]->MeshRender()->SetDynamicShadow(false);
			m_pTrail[i]->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
			//m_pTrail[i]->Transform()->SetLocalScale(Vec3(25.f, 0.1f, 2.5f));
			m_pTrail[i]->Transform()->SetLocalScale(Vec3(10.f, 0.5f, 1.0f));
			m_pTargetObject->AddChild(m_pTrail[i]);
			//CSceneMgr::GetInst()->GetCurScene()->AddGameObject(L"Default", m_pTrail[i], false);
		}
	//}
	//CSceneMgr::GetInst()->GetCurScene()->AddGameObject(L"Default", m_pTrail, false);
}

void CSwordScript::update()
{
	Set_Sword_To_Fbx();
	////Set_SwordTrail();
	////m_pTrail->TrailRenderer()->SetEmit(true);

	////m_pTrail[0]->Transform()->SetQuaternion(qRot);
	////m_pTrail[0]->Transform()->SetLocalRot(vRot);
	//
	if (m_eType == PERSON_OBJ_TYPE::WARRIOR_PLAYER) {
		if ((m_pTargetObject->GetScript<CPlayerScript>()->GetAttack()))
		{
			if (m_pTargetObject->GetScript<CPlayerScript>()->GetMain())
			{
				Vec3 pos = GetObj()->Transform()->GetLocalPos();
				Vec3 rot = m_pTargetObject->Transform()->GetLocalRot();//vRot;//GetObj()->Transform()->GetLocalRot();
				Vec4 qut = qRot;
				Vec3 prev_pos = pos;

				m_fCurTime += DT * 50;

				if (m_iCount == 30) m_iCount = 0;

				if (m_fCurTime > m_fEmitTime) {
					//EmitPoint(m_pObj->Transform()->GetWorldPos());
					Vec3 prev_pos = pos;
					Vec3 prev_rot = rot;
					Vec4 prev_qut = qut;

					m_pTrail[m_iCount]->SetActive(true);
					m_pTrail[m_iCount]->Transform()->SetLocalPos(prev_pos + Vec3(-1.f, 12.5f, 0.f));
					//m_pTrail[m_iCount]->Transform()->SetLocalRot(rot);
					m_pTrail[m_iCount]->Transform()->SetQuaternion(prev_qut);
					m_fLifeTime[m_iCount] += DT * 1.5;

					if (m_fLifeTime[m_iCount] >= 10.f)
					{
						m_fLifeTime[m_iCount] = 0.f;
					}

					m_fCurTime = 0.f;
					m_iCount += 1;
				}
			}
		}

		else {
			for (int i = 0; i < 30; i++) {
				m_pTrail[i]->Transform()->SetLocalPos(Vec3(0.f, 1000.f, 0.f));
			}
		}
	}
}

void CSwordScript::Set_Sword_To_Fbx()
{
	m_pTargetBone = const_cast<tMTBone*>(m_pTargetObject->MeshRender()->GetMesh()->GetBone(m_iTargetBoneIdx));

	vTrans = m_pTargetBone->vecKeyFrame[m_pTargetObject->Animator3D()->GetFrameIdx()].vTranslate;
	qRot = m_pTargetBone->vecKeyFrame[m_pTargetObject->Animator3D()->GetFrameIdx()].qRot;

	switch (m_eType)
	{
	case PERSON_OBJ_TYPE::WARRIOR_PLAYER: {
		vRot = Vec3(0.f, 0.f, XMConvertToRadians(-90.f));
		break;
	}
	case PERSON_OBJ_TYPE::WIZARD_PLAYER:
		break;
	case PERSON_OBJ_TYPE::M_MONSTER:
		vRot = Vec3(0.f, 0.f, XMConvertToRadians(220.f));
		break;
	case PERSON_OBJ_TYPE::FM_MONSTER:
		vRot = Vec3(0.f, 0.f, XMConvertToRadians(45.f));
		break;
	case PERSON_OBJ_TYPE::BOSS:
		vTrans += Vec3(0.f, -10.f, 0.f);
		vRot = Vec3(0.f, XMConvertToRadians(90.f), 0.f);
		break;
	default:
		break;
	}

	Transform()->SetLocalPos(vTrans);
	Transform()->SetQuaternion(qRot);
	Transform()->SetLocalRot(vRot);
}

void CSwordScript::Set_SwordTrail()
{
	Vec3 Prev_vTrans = vTrans;
	Vec4 Prev_qRot = qRot;
	Vec3 Prev_vRot = vRot;

	//if (m_bEmit)
	//{

	//	if (m_fCurTime > m_fEmitTime) {
	//		//EmitPoint(m_pObj->Transform()->GetWorldPos());
	//		m_fCurTime = 0.f;
	//	}

	//}
	//else
	//{
	//	m_fCurTime = 0.f;
	//	//m_iCount = 0.f;
	//}

	//m_pTrail->Transform()->SetLocalPos(vTrans);
	//m_pTrail->Transform()->SetQuaternion(qRot);
	//m_pTrail->Transform()->SetLocalRot(vRot);
}

void CSwordScript::OnCollisionEnter(CCollider2D* _pOther)
{

}

void CSwordScript::OnCollision(CCollider2D* _pOther)
{

}

void CSwordScript::OnCollisionExit(CCollider2D* _pOther)
{

}



