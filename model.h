//=============================================================================
//
// model.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MODEL_H
#define _MODEL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include <vector>

class CModel : public CObject
{
public:

	enum ModelType
	{
		MODEL_JEWEL_TEAR = 0,
		MODEL_CROBAT_BODY,
		MODEL_TREE,
		MODEL_MAX
	};

	CModel();										//コンストラクタ
	CModel(const int nPriority);					//コンストラクタ
	virtual ~CModel() override;						//デストラクタ

	virtual HRESULT Init(void) override;						//初期化処理
	virtual void Uninit(void) override;							//終了処理
	virtual void Update(void) override;							//更新処理
	virtual void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;
	const D3DXVECTOR3 GetPos(void) override;

	void SetRot(const D3DXVECTOR3 ros);
	const D3DXVECTOR3 GetRot(void);

	const D3DXVECTOR2 GetSize(void) override;										//ポリゴンのサイズの取得処理
	const ModelType GetType(void);

	static void LoadAllModels(void);
	static void DestroyAllModels(void);
	static void LoadSavedModels(void);
	static void AddModel(CModel* pModel);

	static void OutputModelData(void);

	static CModel* Create(ModelType type, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CModel* Create(ModelType type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, const int nPriority);

private:

	LPD3DXMESH		m_pMesh;					//メッシュ情報へのポインタ
	LPD3DXBUFFER	m_pBuffMat;					//マテリアル情報へのポインタ
	DWORD			m_nNumMat;					//マテリアル情報の数
	D3DXVECTOR3		m_pos;						//現在の位置
	D3DXVECTOR3		m_LastPos;					//前回の位置
	D3DXVECTOR3		m_move;						//モデルの移動量
	D3DXVECTOR3		m_rot;						//向き
	D3DXVECTOR3		m_minCoord, m_maxCoord;		//モデルの頂点座標の最小値と最大値
	D3DXMATRIX		m_mtxWorld;					//ワールドマトリックス
	ModelType		m_type;						//モデルの種類
												//D3DXVECTOR3		m_rotDestModel;					//目的角度
												//D3DXVECTOR3 Vtx[4];

	static LPD3DXMESH		m_pMeshAll[MODEL_MAX];					//メッシュ情報へのポインタ
	static LPD3DXBUFFER		m_pBuffMatAll[MODEL_MAX];				//マテリアル情報へのポインタ
	static DWORD			m_nNumMatAll[MODEL_MAX];					//マテリアル情報の数
	static char*			m_pModelPass[MODEL_MAX];					//モデルの相対パス
	static std::vector <LPDIRECT3DTEXTURE9> m_vModelTexture[MODEL_MAX];		//モデルのテクスチャへのポインタのベクトル

	static std::vector <CModel*> m_vModel;
};

#endif