//=============================================================================
//
// debugProc.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "debugProc.h"
#include "application.h"
#include "rendering.h"
LPD3DXFONT CDebugProc::m_pFont = nullptr;
std::string CDebugProc::m_str = "";

//コンストラクタ
CDebugProc::CDebugProc()
{

}

//デストラクタ
CDebugProc::~CDebugProc()
{

}

//初期化処理
void CDebugProc::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
}

//終了処理
void CDebugProc::Uninit(void)
{
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//
void CDebugProc::Print(const char *pFormat, ...)
{
	va_list args;

	va_start(args, pFormat);

	for (const char* pPointer = pFormat; *pPointer != '\0'; pPointer++)
	{
		if (*pPointer != '%')
		{
			m_str += *pPointer;
		}
		else
		{
			pPointer++;

			switch (*pPointer)
			{
			case 'd':

			{
				int a = va_arg(args, int);
				m_str += std::to_string(a);
			}

				break;

			case 'f':

			{
				double a = va_arg(args, double);
				m_str += std::to_string(a);
			}

				break;

			case 'c':

			{
				char a = va_arg(args, char);
				m_str += std::to_string(a);
			}

				break;

			case 's':

				m_str += va_arg(args, char*);

				break;

			default:

				m_str += '%';
				m_str += *pPointer;

				break;
			}
		}
	}

	va_end(args);
}

//描画処理
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	TCHAR str[2048];

	if (m_str.length() < 2048)
	{
		sprintf(str, _T(m_str.c_str()));

		// テキスト描画
		m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}

	m_str.clear();
}

CDebugProc* CDebugProc::Create(void)
{
	CDebugProc* pDebug = new CDebugProc;

	if (pDebug != nullptr)
	{
		pDebug->Init();
	}

	return pDebug;
}