//=============================================================================
//
// Letter.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "Letter.h"
#include <string>

//コンストラクタ
CLetter::CLetter()
{
	m_pPreviousLetter = nullptr;
	m_pNextLetter = nullptr;
}

CLetter::CLetter(const int nPriority) : CObject_2D::CObject_2D(nPriority)
{
	m_pPreviousLetter = nullptr;
	m_pNextLetter = nullptr;
}

//デストラクタ
CLetter::~CLetter()
{

}

//初期化処理
HRESULT CLetter::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_pPreviousLetter = nullptr;
	m_pNextLetter = nullptr;

	return S_OK;
}

//終了処理
void CLetter::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CLetter::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();
}

//終了処理
void CLetter::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

bool CLetter::ConvertInNumber(const int nNum)
{
	if (nNum >= 0 && nNum <= 9)
	{
		SetTexture(CObject::TEXTURE_NUMBERS);
		SetTextureParameter(1, 5, 3, INT_MAX);
		SetAnimPattern(nNum);
	}
	else
	{
		return false;
	}

	return true;
}

bool CLetter::ConvertInSymbol(const char symbol)
{
	if (symbol != '?' && symbol != '!' && symbol != '%')
	{
		return false;
	}
	else
	{
		SetTexture(CObject::TEXTURE_NUMBERS);
		SetTextureParameter(1, 5, 3, INT_MAX);

		switch (symbol)
		{
		case '?':

			SetAnimPattern(10);

			break;

		case '!':

			SetAnimPattern(11);

			break;

		case '%':

			SetAnimPattern(12);

			break;

		default:

			return false;

			break;
		}
	}
	
	return true;
}

void CLetter::SetPrevLetter(CLetter* pPrev)
{
	m_pPreviousLetter = pPrev;
}

void CLetter::SetNextLetter(CLetter* pNext)
{
	m_pNextLetter = pNext;
}

CLetter* CLetter::GetPrevLetter(void)
{
	return m_pPreviousLetter;
}

CLetter* CLetter::GetNextLetter(void)
{
	return m_pNextLetter;
}


//==================================================================================================================
//
//		静的関数
//
//==================================================================================================================

//生成処理
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter)
{
	CLetter* pLetter = new CLetter(3);								//生成

																	//初期化処理
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//位置の設定
	pLetter->SetSize(size);									//サイズの設定
															//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//回転角度の設定
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);			//テクスチャの設定
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//テクスチャパラメータの設定

	char aLetter = 33;

	//アニメーションパターンの設定
	int Cell = 27;

	for (int nCnt = 0; nCnt < 93; nCnt++)
	{
		if (letter == aLetter)
		{
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 93)
	{
			pLetter->Release();
			return nullptr;
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}

	return pLetter;
}

//生成処理
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum)
{
	CLetter* pLetter = new CLetter(3);						//生成

																	//初期化処理
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//位置の設定
	pLetter->SetSize(size);									//サイズの設定
															//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//回転角度の設定
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);		//テクスチャの設定
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//テクスチャパラメータの設定

	std::string number = std::to_string(nNum);
	char aLetter = 47;

	//アニメーションパターンの設定
	int Cell = 14;

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		if (number.c_str()[0] == aLetter)
		{
			Cell = nCnt + 14;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 14 || Cell > 56)
	{
		pLetter->Release();
		return nullptr;
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}


	return pLetter;
}

//生成処理
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter, const int nPriority)
{
	CLetter* pLetter = new CLetter(nPriority);						//生成

	//初期化処理
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}
	
	pLetter->SetPos(pos);									//位置の設定
	pLetter->SetSize(size);									//サイズの設定
	//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//回転角度の設定
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);		//テクスチャの設定
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//テクスチャパラメータの設定

	char aLetter = 33;

	//アニメーションパターンの設定
	int Cell = 27;

	for (int nCnt = 0; nCnt < 93; nCnt++)
	{
		if (letter == aLetter)
		{
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 93)
	{
		pLetter->Release();
		return nullptr;
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}

	return pLetter;				
} 

//生成処理
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum, const int nPriority)
{
	//CLetter* pLetter = new CLetter(nPriority);			//生成

	//													//初期化処理
	//if (FAILED(pLetter->Init()))
	//{
	//	return nullptr;
	//}

	//pLetter->SetPos(pos);									//位置の設定
	//pLetter->SetSize(size);									//サイズの設定
	//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//回転角度の設定
	//pLetter->SetTexture(CObject::TEXTURE_LETTERS);			//テクスチャの設定
	//pLetter->SetTextureParameter(26, 13, 2, INT_MAX);		//テクスチャパラメータの設定

	//if (!pLetter->ConvertInNumber(nNum))
	//{
	//	pLetter->Uninit();
	//	pLetter->Release();
	//	return nullptr;
	//}

	CLetter* pLetter = new CLetter(nPriority);						//生成

																	//初期化処理
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//位置の設定
	pLetter->SetSize(size);									//サイズの設定
															//pLetter->SetStartingRot(D3DX_PI * 0.5f);				//回転角度の設定
	pLetter->SetTexture(CObject::TEXTURE_CHARACTERS);		//テクスチャの設定
	pLetter->SetTextureParameter(1, 10, 10, INT_MAX);		//テクスチャパラメータの設定

	std::string number = std::to_string(nNum);
	char aLetter = 47;

	//アニメーションパターンの設定
	int Cell = 14;

	for (int nCnt = 0; nCnt < 10; nCnt++)
	{
		if (number.c_str()[0] == aLetter)
		{
			Cell = nCnt + 14;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 14 || Cell > 56)
	{
		pLetter->Release();
		return nullptr;
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}
	

	return pLetter;
}