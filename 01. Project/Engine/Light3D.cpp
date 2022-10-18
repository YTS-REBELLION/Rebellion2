#include "stdafx.h"
#include "Light3D.h"

#include "Transform.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "SceneMgr.h"
#include "ResMgr.h"

CLight3D::CLight3D()
	: CComponent(COMPONENT_TYPE::LIGHT3D)
	, m_pCamObj(nullptr)
{
	// ���� �������� ī�޶� ����
	m_pCamObj = new CGameObject;
	m_pCamObj->AddComponent(new CTransform);
	m_pCamObj->AddComponent(new CCamera);

	// ������ �����ϴ� ī�޶�� �����Ŵ����� ��ϵǸ� �ȵȴ�.
	m_pCamObj->Camera()->SetModule(true);
	m_pCamObj->Camera()->SetLayerAllCheck(); // ��� ���̾ ��´�(shadow map)
}

CLight3D::~CLight3D()
{
	SAFE_DELETE(m_pCamObj);
}

void CLight3D::SetLightType(LIGHT_TYPE _eType)
{
	m_tLightInfo.iLightType = (int)_eType;

	if (LIGHT_TYPE::DIR == (LIGHT_TYPE)m_tLightInfo.iLightType)
	{
		m_pVolumeMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
		m_pLightMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"DirLightMtrl");
		m_pDepthMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ShadowMapMtrl");

		m_pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHGRAPHIC);
		m_pCamObj->Camera()->SetScale(7.f);
		m_pCamObj->Camera()->SetFar(100000.f);
		m_pCamObj->Camera()->SetWidth(512.f);
		m_pCamObj->Camera()->SetHeight(512.f);
	}
	else if (LIGHT_TYPE::POINT == (LIGHT_TYPE)m_tLightInfo.iLightType)
	{
		m_pVolumeMesh = CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh");
		m_pLightMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PointLightMtrl");
	}
	else if (LIGHT_TYPE::SPOT == (LIGHT_TYPE)m_tLightInfo.iLightType)
	{
		m_pVolumeMesh = CResMgr::GetInst()->FindRes<CMesh>(L"ConeMesh");
	}
}

void CLight3D::SetLightPos(const Vec3 & _vPos)
{
	m_tLightInfo.vLightPos = _vPos;
	Transform()->SetLocalPos(_vPos);
}

void CLight3D::SetLightDir(const Vec3& _vDir)
{
	m_tLightInfo.vLightDir = _vDir;
	m_tLightInfo.vLightDir.Normalize();
	// Transform()->LookAt(_vDir);
	Transform()->LookAt(Vec3(m_tLightInfo.vLightDir.x, m_tLightInfo.vLightDir.y, m_tLightInfo.vLightDir.z));

}

void CLight3D::finalupdate()
{
	m_tLightInfo.vLightPos = Transform()->GetWorldPos();	
	Transform()->SetLocalScale(Vec3(m_tLightInfo.fRange, m_tLightInfo.fRange, m_tLightInfo.fRange));
	m_iArrIdx = CRenderMgr::GetInst()->RegisterLight3D(this);


	//vector<CGameObject*> vectemp;
	//CSceneMgr::GetInst()->FindGameObjectByTag(L"FM_Player", vectemp);
	//if (vectemp.size() == 0)
	//{
	//	// ���� ���� ī�޶� ������ ���� Transform ������ ������ �Ѵ�.
	//	*m_pCamObj->Transform() = *Transform();
	//}
	//else
	//{
	//	// ���� ���� ī�޶� �÷��̾� ������ǥ�� ���Ͽ� ������� ��ġ ������Ʈ
	//	auto a = *Transform();
	//	a.SetLocalPos(a.GetLocalPos() + vectemp[0]->Transform()->GetLocalPos());
	//	*m_pCamObj->Transform() = a;
	//	//Vector3 temp = a.Transform()->GetLocalPos();
	//	//m_pCamObj->Transform()->SetLocalPos(Vector3(temp.x, temp.y, temp.z + 500.f));

	//}

	*m_pCamObj->Transform() = *Transform();
	// �����Ŵ����� ��� �ȉ�.
	m_pCamObj->finalupdate();

}

void CLight3D::render()
{
	if (-1 == m_iArrIdx)
		return;

	// Directional Light �� ���
	if (m_tLightInfo.iLightType == (UINT)LIGHT_TYPE::DIR)
	{
		// ���� ���� ShadowMap �������� �ؽ���
		Ptr<CTexture> pShadowMapTex = CResMgr::GetInst()->FindRes<CTexture>(L"ShadowMapTargetTex");
		m_pLightMtrl->SetData(SHADER_PARAM::TEX_3, pShadowMapTex.GetPointer());

		//Ptr<CTexture> pShadowMapDepthTex = CResMgr::GetInst()->FindRes<CTexture>(L"ShadowMapDepthTex");
		//m_pDepthMtrl->SetData(SHADER_PARAM::TEX_4, pShadowMapDepthTex.GetPointer());

		// �������� ������Ű�� ���� ���� View, Proj ���
		Matrix matVP = m_pCamObj->Camera()->GetViewMat() * m_pCamObj->Camera()->GetProjMat();
		m_pLightMtrl->SetData(SHADER_PARAM::MATRIX_0, &matVP);
	}

	Transform()->UpdateData();
	m_pLightMtrl->SetData(SHADER_PARAM::INT_0, &m_iArrIdx); // ���� �迭 �ε������� ������Ʈ
	m_pLightMtrl->UpdateData(); // int_0, ���� �ε��� , tex_0 : normaltarget, tex_1 : positiontarget 
	m_pVolumeMesh->render();
}

void CLight3D::render_shadowmap()
{
	m_pCamObj->Camera()->SortShadowObject();
	m_pCamObj->Camera()->render_shadowmap();
}

void CLight3D::SaveToScene(FILE * _pFile)
{
}

void CLight3D::LoadFromScene(FILE * _pFile)
{
}