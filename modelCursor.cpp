//=============================================================================
//
// modelCursor.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "modelCursor.h"
#include "debugProc.h"
#include "inputKeyboard.h"
#include "application.h"

//コンストラクタ
CModelCursor::CModelCursor()
{
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_type = (CModel::ModelType)0;
	m_nLockedAxis = 0;
	m_fUpdateSpeed = 0.0f;

	m_pModel = nullptr;
}

//デストラクタ
CModelCursor::~CModelCursor()
{

}


HRESULT CModelCursor::Init(void)
{
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_type = (CModel::ModelType)0;
	m_nLockedAxis = 0;
	m_fUpdateSpeed = 1.0f;

	m_pModel = nullptr;

	return S_OK;
}

void CModelCursor::Uninit(void)
{
	if (m_pModel != nullptr)
	{
		m_pModel->Release();
		m_pModel = nullptr;
	}
}

void CModelCursor::Update(void)
{
	CApplication::MODE mode = CApplication::GetMode();

	if (mode == CApplication::MODE_MODEL)
	{
		if (CInputKeyboard::GetKeyboardTrigger(DIK_Q))
		{
			int type = m_type;
			type--;

			if (type < 0)
			{
				type = CModel::MODEL_MAX - 1;
			}

			m_type = (CModel::ModelType)type;

			ChangeModel();
		}
		if (CInputKeyboard::GetKeyboardTrigger(DIK_E))
		{
			int type = m_type;
			type++;

			if (type >= CModel::MODEL_MAX)
			{
				type = 0;
			}

			m_type = (CModel::ModelType)type;

			ChangeModel();
		}

		if (CInputKeyboard::GetKeyboardPress(DIK_Y))
		{
			if (m_nLockedAxis == 0)
			{
				m_pos.x += m_fUpdateSpeed;
			}
			else if (m_nLockedAxis == 1)
			{
				m_pos.y += m_fUpdateSpeed;
			}
			else
			{
				m_pos.z += m_fUpdateSpeed;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_H))
		{
			if (m_nLockedAxis == 0)
			{
				m_pos.x += -m_fUpdateSpeed;
			}
			else if (m_nLockedAxis == 1)
			{
				m_pos.y += -m_fUpdateSpeed;
			}
			else
			{
				m_pos.z += -m_fUpdateSpeed;
			}
		}


		if (CInputKeyboard::GetKeyboardPress(DIK_B))
		{
			if (m_nLockedAxis == 0)
			{
				m_rot.x += D3DX_PI * 0.05f * m_fUpdateSpeed;
			}
			else if (m_nLockedAxis == 1)
			{
				m_rot.y += D3DX_PI * 0.05f * m_fUpdateSpeed;
			}
			else
			{
				m_rot.z += D3DX_PI * 0.05f * m_fUpdateSpeed;
			}
		}
		else if (CInputKeyboard::GetKeyboardPress(DIK_N))
		{
			if (m_nLockedAxis == 0)
			{
				m_rot.x += -D3DX_PI * 0.05f * m_fUpdateSpeed;
			}
			else if (m_nLockedAxis == 1)
			{
				m_rot.y += -D3DX_PI * 0.05f * m_fUpdateSpeed;
			}
			else
			{
				m_rot.z += -D3DX_PI * 0.05f * m_fUpdateSpeed;
			}
		}

		if (CInputKeyboard::GetKeyboardPress(DIK_LSHIFT) && CInputKeyboard::GetKeyboardTrigger(DIK_R))
		{
			m_rot = Vec3Null;
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_C))
		{
			m_nLockedAxis++;

			if (m_nLockedAxis > 2)
			{
				m_nLockedAxis = 0;
			}
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_NUMPADPLUS))
		{
			m_fUpdateSpeed += 1.0f;
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_NUMPADMINUS))
		{
			if (m_fUpdateSpeed >= 1.0f)
			{
				m_fUpdateSpeed -= 1.0f;
			}
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
		{
			CModel* pModel = CModel::Create(m_type, m_pos, m_rot);

			CModel::AddModel(pModel);
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_F2))
		{
			CModel::OutputModelData();
		}

		if (m_pModel != nullptr)
		{
			m_pModel->SetPos(m_pos);
			m_pModel->SetRot(m_rot);
		}

		char c[8] = {};

		if (m_nLockedAxis == 0)
		{
			strcpy(c, "X");
		}
		if (m_nLockedAxis == 1)
		{
			strcpy(c, "Y");
		}
		else if (m_nLockedAxis == 2)
		{
			strcpy(c, "Z");
		}

		CDebugProc::Print("\nMove Camera on Y Axis: Left CTRL + W/S\n\nLocked Axis: %s\nChange Locked Axis: C\nMove Model on Locked Axis: Y/H\nRotate Model on Locked Axis: B/N\nReset Rotation: Left Shift + R\nCreate Model: Enter\n", c);
		CDebugProc::Print("\n\nMovement Speed: %f\nChange Movement Speed: Numpad + or -", m_fUpdateSpeed);
	}
}

void CModelCursor::Draw(void)
{

}

//位置の設定処理
void CModelCursor::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}


//サイズの取得処理
const D3DXVECTOR2 CModelCursor::GetSize(void)
{
	return Vec2Null;
}

const D3DXVECTOR3 CModelCursor::GetPos(void)
{
	return m_pos;
}






CModelCursor* CModelCursor::Create(CModel::ModelType type, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModelCursor* pModel = new CModelCursor;

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_rot = rot;
	pModel->m_type = type;
	pModel->m_pModel = CModel::Create(type, pos, rot);

	return pModel;
}



void CModelCursor::ChangeModel(void)
{
	if (m_pModel != nullptr)
	{
		m_pModel->Release();
		m_pModel = nullptr;
	}

	m_pModel = CModel::Create(m_type, m_pos, m_rot);
}