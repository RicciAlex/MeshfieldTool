//=============================================================================
//
// light.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "light.h"
#include "application.h"
#include "rendering.h"

CLight* CLight::m_pLight[CLight::MaxLight] = {};

//コンストラクタ
CLight::CLight()
{
	for (int nCnt = 0; nCnt < CLight::MaxLight; nCnt++)
	{
		if (m_pLight[nCnt] == nullptr)
		{
			m_pLight[nCnt] = this;
			m_nIdx = nCnt;
			break;
		}
	}
}

//デストラクタ
CLight::~CLight()
{

}

//ライトの初期化処理
HRESULT CLight::Init(void)
{
	return S_OK;
}

//ライトの終了処理
void CLight::Uninit(void)
{

}

//ライトの更新処理
void CLight::Update(void)
{

}

void CLight::Release(void)
{
	int nIdx = m_nIdx;

	delete m_pLight[nIdx];
	m_pLight[nIdx] = nullptr;
}

const int CLight::GetLightIdx(void)
{
	return m_nIdx;
}





void CLight::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < CLight::MaxLight; nCnt++)
	{
		if (m_pLight[nCnt] != nullptr)
		{
			m_pLight[nCnt]->Release();
		}
	}
}