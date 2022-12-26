//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "application.h"
#include "rendering.h"
#include "object.h"
#include "object2D.h"
#include "input.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "sound.h"
#include "directionalLight.h"
#include "object3D.h"
#include "camera.h"
#include "model.h"
#include "player.h"
#include "debugProc.h"
#include "billboard.h"
#include "meshfield.h"
#include "Letter.h"
#include "UIString.h"
#include "modelCursor.h"

//�ÓI�����o�[�ϐ��̐錾
HWND CApplication::m_hWnd;
CRenderer* CApplication::m_pRenderer = nullptr;			//�����f�B���O�C���X�^���X�ւ̃|�C���^
CInput* CApplication::m_pInput[2] = {};					//�C���v�b�g�C���X�^���X�ւ̃|�C���^
CInputMouse* CApplication::m_pMouse = nullptr;			//�}�E�X�C���X�^���X�ւ̃|�C���^
CSound* CApplication::m_pSound = nullptr;
CFade* CApplication::m_pFade = nullptr;
CCamera* CApplication::m_pCamera = nullptr;
bool CApplication::m_bFade = false;
CPlayer* CApplication::m_pPlayer = nullptr;
CDebugProc* CApplication::m_pDebug = nullptr;
CApplication::MODE CApplication::m_mode = CApplication::MODE_FIELD;

//�R���X�g���N�^
CApplication::CApplication()
{
	
}

//�f�X�g���N�^
CApplication::~CApplication()
{
	
}

//����������
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;

	//�����f�B���O�C���X�^���X�̐�������
	if (m_pRenderer == nullptr)
	{//�|�C���^��null�ł͂Ȃ�������
		m_pRenderer = new CRenderer;
	}

	//�����f�B���O�C���X�^���X�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	m_pDebug = CDebugProc::Create();

	//�e�N�X�`���S�������[�h����
	CObject_2D::LoadTextures();

	//���f���S�������[�h����
	CModel::LoadAllModels();


	//�L�[�{�[�h�C���X�^���X�̐�������
	m_pInput[0] = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	m_pMouse = new CInputMouse;

	if (m_pMouse != nullptr)
	{
		m_pMouse->Init(hInstance, hWnd, GUID_SysMouse);
	}

	m_pSound = CSound::Create(hWnd);

	m_bFade = false;

	CLight::ReleaseAll();
	CDirectionalLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(2, -4, 6));
	CDirectionalLight::Create(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR3(-5, 3, -2));
	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, -200.0f, 300.0f));

	//CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-500.0f, -300.0f, 500.0f), Vec3Null, "data\\FieldData\\VtxSave.txt", 3);
	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-500.0f, -300.0f, 500.0f), Vec3Null, "data\\FieldData\\PitFall_Stage_01.txt", 3);//CMeshfield::Create(D3DXVECTOR3(-500.0f, -300.0f, 500.0f), Vec3Null, D3DXVECTOR2(50.0f, 50.0f), 15, 10, 3);
	//CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-500.0f, -300.0f, 500.0f), Vec3Null, D3DXVECTOR2(50.0f, 50.0f), 10, 20, 3);
	pField->SetTexture(CObject::TEXTURE_BLOCK);
	pField->SetTextureTiling(0.33f);

	CModelCursor* pCursor = CModelCursor::Create(CModel::MODEL_JEWEL_TEAR, pField->GetPos(), Vec3Null);

	//FILE*pFile;				//�t�@�C���|�C���^��錾����

	//						//�t�@�C�����J��
	//pFile = fopen("data\\charData.txt", "wb");

	//if (pFile != NULL)
	//{//�t�@�C�����J�����ꍇ
	// //�t�@�C���Ƀ����L���O���������o��

	//	char cData = 33;		//for (int nCnt = 0; nCnt < 93; nCnt++)
	//	char dData[100] = {};

	//	for (int nCnt = 0; nCnt < 93; nCnt++)
	//	{
	//		dData[nCnt] = cData;

	//		fwrite(&cData, sizeof(char), 1, pFile);

	//		cData++;
	//	}

	//	//�t�@�C�������
	//	fclose(pFile);

	//	int a = 0;
	//}
	//else
	//{//�t�@�C�����J���Ȃ������ꍇ
	//	printf("XXXXX �Z�[�u�t�@�C�����J���܂���ł��� XXXXX");
	//}

	return S_OK;
}

//�I������
void CApplication::Uninit(void)
{
	//�����f�B���O�C���X�^���X�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//�C���v�b�g�f�o�C�X�̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Uninit();
			delete m_pInput[nCnt];
			m_pInput[nCnt] = nullptr;
		}
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Uninit();
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pDebug != nullptr)
	{
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	//�I�u�W�F�N�g�S�̂̏I������
	CObject::ReleaseAll();

	CLight::ReleaseAll();

	//�e�N�X�`���S���̔j��
	CObject_2D::DestroyLoadedTextures();

	//���f���S���j���̔j������
	CModel::DestroyAllModels();
}

//�X�V����
void CApplication::Update(void)
{
	CDebugProc::Print("\nWASD�L�[�Ŏ��_�̈ړ�\n�}�E�X�Œ����_�̈ړ�\n\nChange Mode SPACE");

	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE))
	{
		if (m_mode == MODE_FIELD)
		{
			m_mode = MODE_MODEL;
		}
		else
		{
			m_mode = MODE_FIELD;
		}
	}

	if (m_mode == MODE_FIELD)
	{
		CDebugProc::Print("\nPresent Mode: FIELD MODIFY MODE\n");
	}
	else if (m_mode == MODE_MODEL)
	{
		CDebugProc::Print("\nPresent Mode: MODEL SET MODE\n");
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Update();
	}

	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
	}
}

//�`�揈��
void CApplication::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

CRenderer* CApplication::GetRenderer(void)
{
	return m_pRenderer;
}

CInputMouse* CApplication::GetMouse(void)
{
	return m_pMouse;
}

HWND CApplication::GetWindow(void)
{
	return m_hWnd;
}

//�T�E���h�̎擾����
CSound* CApplication::GetSound(void)
{
	return m_pSound;
}

CCamera* CApplication::GetCamera(void)
{
	return m_pCamera;
}

CPlayer* CApplication::GetPlayer(void)
{
	return m_pPlayer;
}

CApplication::MODE CApplication::GetMode(void)
{
	return m_mode;
}
