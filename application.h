//=============================================================================
//
// application.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef APPLICATION_H
#define APPLICATION_H

//�C���N���[�h�t�@�C��
#include "object.h"

//�O���錾
class CRenderer;
class CInput;
class CInputMouse;
class CSound;
class CFade;
class CCamera;
class CPlayer;
class CDebugProc;

//�A�v���P�[�V�����̃N���X
class CApplication
{
public:

	enum MODE
	{
		MODE_FIELD = 0,
		MODE_MODEL,

		MODE_MAX
	};

	CApplication();										//�R���X�g���N�^
	~CApplication();									//�f�X�g���N�^
														
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	static CRenderer* GetRenderer(void);				//�����f�B���O�C���X�^���X�̎擾����
	static CInputMouse* GetMouse(void);					//�}�E�X�C���X�^���X�̎擾����
	static HWND GetWindow(void);
	static CSound* GetSound(void);
	static CCamera* GetCamera(void);
	static CPlayer* GetPlayer(void);
	static MODE GetMode(void);

private:

	static HWND m_hWnd;									//�N���C�G���g���
	static CRenderer* m_pRenderer;						//�����f�B���O�C���X�^���X�ւ̃|�C���^
	static CInput* m_pInput[2];							//�C���v�b�g�f�o�C�X�ւ̃|�C���^
	static CInputMouse* m_pMouse;						//�}�E�X�C���X�^���X
	static CSound* m_pSound;
	static CFade* m_pFade;
	static CCamera* m_pCamera;
	static CPlayer* m_pPlayer;
	static MODE m_mode;

	static CDebugProc* m_pDebug;

	static bool m_bFade;
};



#endif // !APPLICATION_H
