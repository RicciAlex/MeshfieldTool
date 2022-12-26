//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CModel;

class CPlayer
{
public:
	CPlayer();											//コンストラクタ
	~CPlayer();									//デストラクタ

	HRESULT Init(void);						//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	void SetPos(const D3DXVECTOR3 pos);				//位置の設定処理

	const D3DXVECTOR2 GetSize(void);				//サイズの取得処理
	const D3DXVECTOR3 GetPos(void);

	D3DXVECTOR3 GetDestRot(void) { return m_DestRot; };

	static CPlayer* Create(const D3DXVECTOR3 pos);

private:

	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_move;									//速度
	D3DXVECTOR3 m_DestRot;

	CModel* m_pModel;									//モデル
};

#endif