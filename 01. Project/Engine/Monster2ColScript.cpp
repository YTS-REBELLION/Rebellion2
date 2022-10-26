#include "stdafx.h"
#include "Monster2ColScript.h"
#include "MonsterScript2.h"

CMonster2ColScript::CMonster2ColScript() :CScript((UINT)SCRIPT_TYPE::OBJCOLSCRIPT) {


}
CMonster2ColScript::~CMonster2ColScript() {

}
void CMonster2ColScript::OnCollisionEnter(CCollider2D* _pOther)
{
	m_pMonster->GetScript<CMonsterScript2>()->OnCollisionEnter(_pOther);
}
void CMonster2ColScript::OnCollision(CCollider2D* _pOther)
{
	m_pMonster->GetScript<CMonsterScript2>()->OnCollision(_pOther);
}
void CMonster2ColScript::OnCollisionExit(CCollider2D* _pOther)
{
	m_pMonster->GetScript<CMonsterScript2>()->OnCollisionExit(_pOther);
}

void CMonster2ColScript::update() {

	Vec3 vRot = Transform()->GetLocalRot();
	vRot = m_vCalRot;
	Transform()->SetLocalPos(m_pMonster->Transform()->GetLocalPos());
	Transform()->SetLocalRot(vRot);

	m_vCalRot = Vec3();
}