//=============================================================================
//
// directionalLight.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "directionalLight.h"
#include "application.h"
#include "rendering.h"

//コンストラクタ
CDirectionalLight::CDirectionalLight()
{
	ZeroMemory(&m_pDirLight, sizeof(D3DLIGHT9));
}

//デストラクタ
CDirectionalLight::~CDirectionalLight()
{

}

//初期化処理
HRESULT CDirectionalLight::Init(void)
{
	ZeroMemory(&m_pDirLight, sizeof(m_pDirLight));

	return S_OK;
}

//終了処理
void CDirectionalLight::Uninit(void)
{

}

//更新処理
void CDirectionalLight::Update(void)
{

}



CDirectionalLight* CDirectionalLight::Create(D3DXCOLOR col, D3DXVECTOR3 dir)
{
	CDirectionalLight* pLight = new CDirectionalLight;

	if (FAILED(pLight->Init()))
	{
		return nullptr;
	}

	pLight->m_pDirLight.Type = D3DLIGHT_DIRECTIONAL;
	pLight->m_pDirLight.Diffuse = col;
	pLight->m_pDirLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 newDir;
	D3DXVec3Normalize(&newDir, &dir);
	pLight->m_pDirLight.Direction = dir;

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	pDevice->SetLight(pLight->GetLightIdx(), &pLight->m_pDirLight);
	pDevice->LightEnable(pLight->GetLightIdx(), TRUE);

	return pLight;
}