#include "stdafx.h"
#include "Trail.h"
#include "StructuredBuffer.h"
#include "ResMgr.h"
#include "Transform.h"

void CTrail::update()
{

}

void CTrail::finalUpdate()
{

}

void CTrail::render()
{
	//Transform()->UpdateData();

	//m_pMtrl->UpdateData();
}

void CTrail::init(Ptr<CTexture> _pTexture)
{
	//m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
	//m_pMtrl = new CMaterial;
	//m_pMtrl->SetShader(CResMgr::GetInst()->FindRes<CShader>(L"TrailShader"));
	//Ptr<CTexture> pTrailTex = _pTexture;
	//m_pMtrl->SetData(SHADER_PARAM::TEX_0, pTrailTex.GetPointer());
}

CTrail::CTrail()
{

}

CTrail::~CTrail()
{
}