//=============================================================================
//
// meshfield.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include <vector>

class CMeshfield : public CObject
{
public:

	enum MODE
	{
		MODE_NULL,
		MODE_MESHFIELD,
		MODE_MODEL,
		MODE_MAX
	};

	CMeshfield();										//コンストラクタ
	CMeshfield(const int nPriority);										//コンストラクタ
	~CMeshfield() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	void SetTexture(CObject::TextType texture);			//テクスチャの設定処理
	void SetTextureTiling(D3DXVECTOR2 TileSize);
	void SetTextureTiling(float fTileSize);

	static void AddLine(const bool bBottom);
	static void AddColumn(const bool bRight);

	static void CutLine(const bool bBottom);
	static void CutColumn(const bool bRight);

	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,
		const D3DXVECTOR2 unitSize, const int NumberLines, const int NumberColumns);								//生成処理
	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, 
		const D3DXVECTOR2 unitSize, const int NumberLines, const int NumberColumns, const int nPriority);			//生成処理
	static CMeshfield* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, char* pPass, const int nPriority);		//生成処理


private:

	void SetVertex(void);								//頂点インデックスの設定処理
	void LoadVertex(void);								//頂点インデックスのロード処理

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;					//インデックスバッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;							//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_rot;									//向き
	D3DXVECTOR2 m_size;									//単位のサイズ
	D3DXMATRIX m_mtxWorld;								//ワルドマトリックス
	//std::vector <D3DXCOLOR> vColor;						//頂点カラー
	int m_nUpdatingVtxIdx;
	int m_nLockedAxis;
	int m_nVertexNumber;								//メッシュフィールドの頂点数
	int m_nIndexNumber;									//メッシュフィールドのインデックス数
	int m_nPolygonNumber;								//メッシュフィールドのポリゴン数
	int m_nLineVertex;									//計算用のグローバル変数(列数 + 1)
	int m_nColumnVertex;								//計算用のグローバル変数(行数 + 1)
	D3DXVECTOR2 m_fTextTiling;
	bool m_bRead;
	bool m_bWire;
	bool m_bReturnToDefault;
	float m_fSavedValue;
	float m_fSavedTexValue;

	char* m_pPass;

	static float m_fStaticSize;
	static CMeshfield* m_pPresentField;
};


#endif