//=============================================================================
//
// application.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef APPLICATION_H
#define APPLICATION_H

//インクルードファイル
#include "object.h"

//前方宣言
class CRenderer;
class CInput;
class CInputMouse;
class CSound;
class CFade;
class CCamera;
class CPlayer;
class CDebugProc;

//アプリケーションのクラス
class CApplication
{
public:

	enum MODE
	{
		MODE_FIELD = 0,
		MODE_MODEL,

		MODE_MAX
	};

	CApplication();										//コンストラクタ
	~CApplication();									//デストラクタ
														
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
	static CRenderer* GetRenderer(void);				//レンディングインスタンスの取得処理
	static CInputMouse* GetMouse(void);					//マウスインスタンスの取得処理
	static HWND GetWindow(void);
	static CSound* GetSound(void);
	static CCamera* GetCamera(void);
	static CPlayer* GetPlayer(void);
	static MODE GetMode(void);

private:

	static HWND m_hWnd;									//クライエント画面
	static CRenderer* m_pRenderer;						//レンディングインスタンスへのポインタ
	static CInput* m_pInput[2];							//インプットデバイスへのポインタ
	static CInputMouse* m_pMouse;						//マウスインスタンス
	static CSound* m_pSound;
	static CFade* m_pFade;
	static CCamera* m_pCamera;
	static CPlayer* m_pPlayer;
	static MODE m_mode;

	static CDebugProc* m_pDebug;

	static bool m_bFade;
};



#endif // !APPLICATION_H
