//=============================================================================
//
// player.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "camera.h"
#include "application.h"
#include "debugProc.h"

//コンストラクタ
CPlayer::CPlayer()
{
	m_move = Vec3Null;
	m_DestRot = Vec3Null;

	m_pModel = nullptr;
}

//デストラクタ
CPlayer::~CPlayer()
{

}

//初期化処理
HRESULT CPlayer::Init(void)
{
	m_move = Vec3Null;
	m_DestRot = Vec3Null;

	m_pModel = nullptr;

	return S_OK;
}

//終了処理
void CPlayer::Uninit(void)
{
	if (m_pModel != nullptr)
	{
		m_pModel->Release();
		m_pModel = nullptr;
	}
}

//更新処理
void CPlayer::Update(void)
{
	if (m_pModel != nullptr)
	{
		D3DXVECTOR3 cameraRot = CApplication::GetCamera()->GetRot();
		D3DXVECTOR3 cR = D3DXVECTOR3(-cosf(cameraRot.y), 0.0f, sinf(cameraRot.y));
		float fA = acosf(cR.x);

		if (cR.z < 0.0f)
		{
			fA *= -1.0f;
		}


		if (CInputKeyboard::GetKeyboardPress(DIK_W))
		{			
			if (CInputKeyboard::GetKeyboardPress(DIK_A))
			{
				if (m_move.x <= 4.0f && m_move.x >= -4.0f)
				{
					m_move.x += 0.5f * cosf(D3DX_PI * 0.25f + cameraRot.y);
				}
				if (m_move.z <= 4.0f && m_move.z >= -4.0f)
				{
					m_move.z += 0.5f * sinf(D3DX_PI * 0.25f + cameraRot.y);
				}

				m_DestRot.y = D3DX_PI * 0.25f + fA;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D))
			{
				if (m_move.x <= 4.0f && m_move.x >= -4.0f)
				{
					m_move.x += 0.5f * cosf(-D3DX_PI * 0.25f + cameraRot.y);
				}
				if (m_move.z <= 4.0f && m_move.z >= -4.0f)
				{
					m_move.z += 0.5f * sinf(-D3DX_PI * 0.25f + cameraRot.y);
				}

				m_DestRot.y = D3DX_PI * 0.75f + fA;
			}
			else
			{
				if (m_move.x <= 4.0f && m_move.x >= -4.0f)
				{
					m_move.x += 0.5f * cosf(cameraRot.y);
				}
				if (m_move.z <= 4.0f && m_move.z >= -4.0f)
				{
					m_move.z += 0.5f * sinf(cameraRot.y);
				}

				m_DestRot.y = D3DX_PI * 0.5f + fA;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_S))
		{
			if (CInputKeyboard::GetKeyboardPress(DIK_A))
			{
				if (m_move.x <= 4.0f && m_move.x >= -4.0f)
				{
					m_move.x += 0.5f * cosf(D3DX_PI * 0.75f + cameraRot.y);
				}
				if (m_move.z <= 4.0f && m_move.z >= -4.0f)
				{
					m_move.z += 0.5f * sinf(D3DX_PI * 0.75f + cameraRot.y);
				}

				m_DestRot.y = -D3DX_PI * 0.25f + fA;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_D))
			{
				if (m_move.x <= 4.0f && m_move.x >= -4.0f)
				{
					m_move.x += 0.5f * cosf(-D3DX_PI * 0.75f + cameraRot.y);
				}
				if (m_move.z <= 4.0f && m_move.z >= -4.0f)
				{
					m_move.z += 0.5f * sinf(-D3DX_PI * 0.75f + cameraRot.y);
				}

				m_DestRot.y = -D3DX_PI * 0.75f + fA;
			}
			else
			{
				if (m_move.x <= 4.0f && m_move.x >= -4.0f)
				{
					m_move.x += 0.5f * cosf(D3DX_PI + cameraRot.y);
				}
				if (m_move.z <= 4.0f && m_move.z >= -4.0f)
				{
					m_move.z += 0.5f * sinf(D3DX_PI + cameraRot.y);
				}

				m_DestRot.y = -D3DX_PI * 0.5f + fA;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(-D3DX_PI * 0.5f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(-D3DX_PI * 0.5f + cameraRot.y);
			}

			m_DestRot.y = D3DX_PI + fA;
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{
			if (m_move.x <= 4.0f && m_move.x >= -4.0f)
			{
				m_move.x += 0.5f * cosf(D3DX_PI * 0.5f + cameraRot.y);
			}
			if (m_move.z <= 4.0f && m_move.z >= -4.0f)
			{
				m_move.z += 0.5f * sinf(D3DX_PI * 0.5f + cameraRot.y);
			}

			m_DestRot.y = fA;
		}		

		m_pModel->SetPos(m_pModel->GetPos() + m_move);

		m_move.x += (0.0f - m_move.x) * 0.1f;
		m_move.y += (0.0f - m_move.y) * 0.1f;
		m_move.z += (0.0f - m_move.z) * 0.1f;

		/*if (m_DestRot.y > D3DX_PI)
		{
			m_DestRot.y -= 2.0f * D3DX_PI;
		}
		else if (m_DestRot.y < D3DX_PI)
		{
			m_DestRot.y += 2.0f * D3DX_PI;
		}*/

		if (m_DestRot.y - (m_pModel->GetRot().y) > D3DX_PI)
		{
			m_DestRot.y -= 2 * D3DX_PI;
		}
		else if (m_DestRot.y - (m_pModel->GetRot().y) < -D3DX_PI)
		{
			m_DestRot.y += 2 * D3DX_PI;
		}

		D3DXVECTOR3 rot = m_pModel->GetRot() + ((m_DestRot - m_pModel->GetRot()) * 0.1f);

		m_pModel->SetRot(rot);		

		{
			float fRot = m_pModel->GetRot().y;

			if (fRot > D3DX_PI)
			{
				fRot = -D3DX_PI + (fRot - D3DX_PI);
			}
			else if (fRot < -D3DX_PI)
			{
				fRot = D3DX_PI - (D3DX_PI + fRot);
			}

			if (fRot < D3DX_PI * -2.0f)
			{
				fRot += D3DX_PI * 2.0f;
			}
			else if (fRot > D3DX_PI * 2.0f)
			{
				fRot += D3DX_PI * -2.0f;
			}

			m_pModel->SetRot(D3DXVECTOR3(m_pModel->GetRot().x, fRot, m_pModel->GetRot().z));
		}

		CDebugProc::Print("\nRot: %f\nRot Dest: %f", m_pModel->GetRot().y, m_DestRot.y);
	}
}

//描画処理
void CPlayer::Draw(void)
{
	if (m_pModel != nullptr)
	{
		m_pModel->Draw();
	}
}

//位置の設定処理
void CPlayer::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの取得処理
const D3DXVECTOR2 CPlayer::GetSize(void)
{
	return Vec2Null;
}

//位置の取得処理
const D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}



//生成処理
CPlayer* CPlayer::Create(const D3DXVECTOR3 pos)
{
	CPlayer* pModel = new CPlayer;
	
	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	//pModel->m_pModel = CModel::Create(CModel::MODEL_CROBAT_BODY, pos);

	/*if (pModel->m_pModel != nullptr)
	{
		pModel->m_pModel->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
	}*/

	return pModel;
}