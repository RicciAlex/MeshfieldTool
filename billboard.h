//=============================================================================
//
// billboard.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

class CBillboard : public CObject
{
public:
	CBillboard();										//コンストラクタ
	CBillboard(const int nPriority);					//コンストラクタ
	~CBillboard() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetSize(const D3DXVECTOR2 size);				//サイズの設定処理
	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理
	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	void SetTexture(TextType textType);												//テクスチャの種類の設定処理

	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, const int nPriority);
		
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//頂点バッファ
	LPDIRECT3DTEXTURE9 m_pTexture;						//テクスチャ情報へのポインタ

	D3DXVECTOR3 m_pos;									//ポリゴンの位置
	D3DXVECTOR3 m_rot;									//ポリゴンの回転角度
	D3DXVECTOR3 m_fFrameRot;							//1フレームの回転角度
	D3DXVECTOR2 m_size;									//ポリゴンの幅と高さ
	D3DXMATRIX m_mtxWorld;								//ワールドマトリックス
};

#endif