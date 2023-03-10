//=============================================================================
//
// camera.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "camera.h"
#include "application.h"
#include "rendering.h"
#include "inputMouse.h"
#include "inputKeyboard.h"
#include "debugProc.h"

//コンストラクタ
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点
	m_DestPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目的の視点
	m_DestPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目的の注視点
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目的の向き
	m_fDistance = 0.0f;				//視点からプレイヤーまでの距離
	m_fDistanceFocalPoint = 0.0f;		//注視点からプレイヤーまでの距離
	m_fLenght = 0.0f;
	m_nDelay = 0;
}

//デストラクタ
CCamera::~CCamera()
{

}

//初期化処理
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点
	m_DestPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目的の視点
	m_DestPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目的の注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//上方向ベクトル
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//目的の向き
	m_fDistance = 0.0f;				//視点からプレイヤーまでの距離
	m_fDistanceFocalPoint = 0.0f;		//注視点からプレイヤーまでの距離
	m_fLenght = 0.0f;
	m_nDelay = 0;

	return S_OK;
}

//終了処理
void CCamera::Uninit(void)
{

}

//更新処理
void CCamera::Update(void)
{
#ifndef DEBUG

	if (CInputKeyboard::GetKeyboardPress(DIK_A))
	{
		D3DXVECTOR3 v = m_posR - m_posV;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		float fDot = D3DXVec3Dot(&v, &unit);
		float fAngle = acosf(fDot);
		if (v.z < 0.0f)
		{
			fAngle *= -1.0f;
		}

		fAngle += D3DX_PI * 0.5f;
		m_posV.x += cosf(fAngle) * 5.0f;
		m_posV.z += sinf(fAngle) * 5.0f;
		m_posR.x += cosf(fAngle) * 5.0f;
		m_posR.z += sinf(fAngle) * 5.0f;

	}
	if (CInputKeyboard::GetKeyboardPress(DIK_W))
	{
		if (!CInputKeyboard::GetKeyboardPress(DIK_LCONTROL))
		{
			D3DXVECTOR3 v = m_posR - m_posV;
			v.y = 0.0f;
			D3DXVec3Normalize(&v, &v);
			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			float fDot = D3DXVec3Dot(&v, &unit);
			float fAngle = acosf(fDot);
			if (v.z < 0.0f)
			{
				fAngle *= -1.0f;
			}

			m_posV.x += cosf(fAngle) * 5.0f;
			m_posV.z += sinf(fAngle) * 5.0f;
			m_posR.x += cosf(fAngle) * 5.0f;
			m_posR.z += sinf(fAngle) * 5.0f;
		}
		else
		{
			m_posR.y += 1.0f;
			m_posV.y += 1.0f;
		}
	}
	if (CInputKeyboard::GetKeyboardPress(DIK_D))
	{
		D3DXVECTOR3 v = m_posR - m_posV;
		v.y = 0.0f;
		D3DXVec3Normalize(&v, &v);
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		float fDot = D3DXVec3Dot(&v, &unit);
		float fAngle = acosf(fDot);
		if (v.z < 0.0f)
		{
			fAngle *= -1.0f;
		}

		fAngle += -D3DX_PI * 0.5f;
		m_posV.x += cosf(fAngle) * 5.0f;
		m_posV.z += sinf(fAngle) * 5.0f;
		m_posR.x += cosf(fAngle) * 5.0f;
		m_posR.z += sinf(fAngle) * 5.0f;
	}
	if (CInputKeyboard::GetKeyboardPress(DIK_S))
	{
		if (!CInputKeyboard::GetKeyboardPress(DIK_LCONTROL))
		{
			D3DXVECTOR3 v = m_posR - m_posV;
			v.y = 0.0f;
			D3DXVec3Normalize(&v, &v);
			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			float fDot = D3DXVec3Dot(&v, &unit);
			float fAngle = acosf(fDot);
			if (v.z < 0.0f)
			{
				fAngle *= -1.0f;
			}

			fAngle += D3DX_PI;
			m_posV.x += cosf(fAngle) * 5.0f;
			m_posV.z += sinf(fAngle) * 5.0f;
			m_posR.x += cosf(fAngle) * 5.0f;
			m_posR.z += sinf(fAngle) * 5.0f;
		}
		else
		{
			m_posR.y += -1.0f;
			m_posV.y += -1.0f;
		}
	}

	DIMOUSESTATE* pMouse = CApplication::GetMouse()->GetMouseState();

	if (pMouse->lY > 0)
	{
		if (m_posR.y > m_posV.y - 500.0f)
		{
			m_posR.y += -5.0f;
		}
	}
	else if (pMouse->lY < 0)
	{
		if (m_posR.y < m_posV.y + 500.0f)
		{
			m_posR.y += 5.0f;
		}
	}
	if (pMouse->lX > 0)
	{
		m_rot.y += -D3DX_PI * 0.005f;
	}
	else if (pMouse->lX < 0)
	{
		m_rot.y += D3DX_PI * 0.005f;
	}

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= 2.0f * D3DX_PI;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += 2.0f * D3DX_PI;
	}

	m_posR.x = m_posV.x + m_fLenght * cosf(m_rot.y);
	m_posR.z = m_posV.z + m_fLenght * sinf(m_rot.y);

#endif // DEBUG

}

//設定処理
void CCamera::Set(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

const D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//カメラの向きの取得処理
const D3DXVECTOR3 CCamera::GetDirection(void)
{
	D3DXVECTOR3 dir = m_posR - m_posV;
	D3DXVec3Normalize(&dir, &dir);

	return dir;
}

CCamera* CCamera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 focalPoint)
{
	CCamera* pCamera = new CCamera;

	if (FAILED(pCamera->Init()))
	{
		return nullptr;
	}

	pCamera->m_posV = pos;
	pCamera->m_posR = focalPoint;

	D3DXVECTOR3 v = pCamera->m_posR - pCamera->m_posV;
	D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&v, &v);

	pCamera->m_rot.y = acosf(D3DXVec3Dot(&v, &unit));
	if (pCamera->m_posR.z < pCamera->m_posV.z)
	{
		pCamera->m_rot.y *= -1.0f;
	}

	pCamera->m_fLenght = sqrtf(((pCamera->m_posR.x - pCamera->m_posV.x) * (pCamera->m_posR.x - pCamera->m_posV.x)) + ((pCamera->m_posR.z - pCamera->m_posV.z) * (pCamera->m_posR.z - pCamera->m_posV.z)));

	return pCamera;
}