//=============================================================================
//
// model.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"
#include "application.h"
#include "object2D.h"
#include "rendering.h"
#include "modelCursor.h"
#include <string>

LPD3DXMESH		CModel::m_pMeshAll[MODEL_MAX] = {};					//メッシュ情報へのポインタ
LPD3DXBUFFER	CModel::m_pBuffMatAll[MODEL_MAX] = {};				//マテリアル情報へのポインタ
DWORD			CModel::m_nNumMatAll[MODEL_MAX] = {};				//マテリアル情報の数
std::vector <LPDIRECT3DTEXTURE9>     CModel::m_vModelTexture[CModel::MODEL_MAX];		//モデルのテクスチャへのポインタのベクトル
std::vector <CModel*> CModel::m_vModel;

char*			CModel::m_pModelPass[MODEL_MAX] =
{
	{ "data\\MODELS\\Tear.x" },
	{ "data\\MODELS\\CrobatBody.x" },
	{ "data\\MODELS\\Tree.x" }
};

//コンストラクタ
CModel::CModel()
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;								//モデルの頂点座標の最小値と最大値
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_type = CModel::MODEL_JEWEL_TEAR;
}

CModel::CModel(const int nPriority) : CObject::CObject(nPriority)
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;								//モデルの頂点座標の最小値と最大値
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_type = CModel::MODEL_JEWEL_TEAR;
}

//デストラクタ
CModel::~CModel()
{

}

//初期化処理
HRESULT CModel::Init(void)
{
	m_pMesh = nullptr;								//メッシュ情報へのポインタ
	m_pBuffMat = nullptr;							//マテリアル情報へのポインタ
	m_nNumMat = 0;									//マテリアル情報の数
	m_pos = Vec3Null;								//現在の位置
	m_LastPos = Vec3Null;							//前回の位置
	m_move = Vec3Null;								//モデルの移動量
	m_rot = Vec3Null;								//向き
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;							//モデルの頂点座標の最小値と最大値
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス

													/*std::vector <LPDIRECT3DTEXTURE9> v;

													v.clear();

													LPDIRECT3DTEXTURE9 pText = CObject_2D::GetTexturePointer(CObject::TextureNumbers);

													v.push_back(nullptr);
													v.push_back(pText);

													LPDIRECT3DTEXTURE9 a = v.data()[0];
													LPDIRECT3DTEXTURE9 b = v.data()[1];*/

	return S_OK;
}

//終了処理
void CModel::Uninit(void)
{

}

//更新処理
void CModel::Update(void)
{

}

//描画処理
void CModel::Draw(void)
{
	CApplication::MODE mode = CApplication::GetMode();

	if (mode == CApplication::MODE_MODEL)
	{
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//デバイスの取得
		D3DXMATRIX mtxRot, mtxTrans;							//計算用マトリックス
		D3DMATERIAL9 matDef;									//現在のマテリアル保存用
		D3DXMATERIAL *pMat;										//マテリアルデータへのポインタ

																//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

																//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//現在のマテリアルを保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

			//モデルパーツの描画
			m_pMesh->DrawSubset(nCntMat);
		}

		//保持しいたマテリアルを戻す
		pDevice->SetMaterial(&matDef);

		//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//位置の設定処理
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

void CModel::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

const D3DXVECTOR3 CModel::GetRot(void)
{
	return m_rot;
}

//ポリゴンのサイズの取得処理
const D3DXVECTOR2 CModel::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

const CModel::ModelType CModel::GetType(void)
{
	return m_type;
}






//モデル全部の読み込み処理
void CModel::LoadAllModels(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		m_vModelTexture[nCnt].clear();

		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_pModelPass[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatAll[nCnt],
			NULL,
			&m_nNumMatAll[nCnt],
			&m_pMeshAll[nCnt]);

		D3DXMATERIAL *pMat = nullptr;

		//マテリアルデータへのポインタの取得
		pMat = (D3DXMATERIAL*)m_pBuffMatAll[nCnt]->GetBufferPointer();

		for (int a = 0; a < (int)m_nNumMatAll[nCnt]; a++)
		{
			LPDIRECT3DTEXTURE9 pTex = nullptr;

			D3DXCreateTextureFromFile(pDevice, pMat->pTextureFilename, &pTex);
			pMat++;
			m_vModelTexture[nCnt].push_back(pTex);
		}
	}
}

//モデル全部の破棄処理
void CModel::DestroyAllModels(void)
{
	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		if (m_pMeshAll[nCnt] != nullptr)
		{
			m_pMeshAll[nCnt]->Release();
			m_pMeshAll[nCnt] = nullptr;
		}

		if (m_pBuffMatAll[nCnt] != nullptr)
		{
			m_pBuffMatAll[nCnt]->Release();
			m_pBuffMatAll[nCnt] = nullptr;
		}
	}
}

void CModel::LoadSavedModels(void)
{
	m_vModel.clear();
	FILE* pFile = fopen("data\\MODELS\\ModelSetData\\ModelSetData.txt", "r");

	if (pFile != nullptr)
	{
		int nType = 0;
		D3DXVECTOR3 pos = Vec3Null;
		D3DXVECTOR3 rot = Vec3Null;
		char aStr[512] = {};

		fscanf(pFile, "%s", aStr);

		while (strcmp(aStr, "END_SCRIPT") != 0)
		{
			fscanf(pFile, "%s", aStr);

			if (strcmp(aStr, "BEGIN") == 0)
			{
				while (strcmp(aStr, "END") != 0)
				{
					fscanf(pFile, "%s", aStr);

					if (strcmp(aStr, "POS:") == 0)
					{
						std::string s;
						fscanf(pFile, "%s", aStr);
						s = aStr;
						float fNum = std::stof(s);
						pos.x = fNum;

						fscanf(pFile, "%s", aStr);
						s = aStr;
						fNum = std::stof(s);
						pos.y = fNum;

						fscanf(pFile, "%s", aStr);
						s = aStr;
						fNum = std::stof(s);
						pos.z = fNum;
					}
					else if (strcmp(aStr, "ROT:") == 0)
					{
						std::string s;
						fscanf(pFile, "%s", aStr);
						s = aStr;
						float fNum = std::stof(s);
						rot.x = fNum;

						fscanf(pFile, "%s", aStr);
						s = aStr;
						fNum = std::stof(s);
						rot.y = fNum;

						fscanf(pFile, "%s", aStr);
						s = aStr;
						fNum = std::stof(s);
						rot.z = fNum;
					}
					else if (strcmp(aStr, "TYPE:") == 0)
					{
						fscanf(pFile, "%d", &nType);
					}
				}

				CModel* pModel = CModel::Create((ModelType)nType, pos, rot);
				m_vModel.push_back(pModel);
			}
		}
	}

	fclose(pFile);
}

void CModel::AddModel(CModel* pModel)
{
	m_vModel.push_back(pModel);
}

void CModel::OutputModelData(void)
{
	FILE* pFile = fopen("data\\MODELS\\ModelSetData\\ModelSetData.txt", "w");

	if (pFile != nullptr)
	{
		fprintf(pFile, "\n\nTOT MODELS: %d\n\n", (int)m_vModel.size());

		for (int nCnt = 0; nCnt < (int)m_vModel.size(); nCnt++)
		{
			CModel* pModel = m_vModel.data()[nCnt];

			if (pModel != nullptr)
			{
				D3DXVECTOR3 pos, rot;
				pos = pModel->GetPos();
				rot = pModel->GetRot();
				int nType = pModel->GetType();
				fprintf(pFile, "\nModel %d\n\nBEGIN\n\nTYPE: %d\nPOS: %f %f %f\nROT: %f %f %f\n\nEND\n\n", nCnt, nType, pos.x, pos.y, pos.z, rot.x, rot.y, rot.z);
			}
		}

		fprintf(pFile, "\n\nEND_SCRIPT");
	}

	fclose(pFile);
}

//生成処理
CModel* CModel::Create(ModelType type, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel* pModel = new CModel(3);

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_LastPos = pos;
	pModel->m_move = Vec3Null;
	pModel->m_rot = rot;
	pModel->m_pMesh = m_pMeshAll[type];
	pModel->m_pBuffMat = m_pBuffMatAll[type];
	pModel->m_nNumMat = m_nNumMatAll[type];
	pModel->m_type = type;

	return pModel;
}

CModel* CModel::Create(ModelType type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, const int nPriority)
{
	CModel* pModel = new CModel(nPriority);

	if (FAILED(pModel->Init()))
	{
		return nullptr;
	}

	pModel->m_pos = pos;
	pModel->m_LastPos = pos;
	pModel->m_move = Vec3Null;
	pModel->m_rot = rot;
	pModel->m_pMesh = m_pMeshAll[type];
	pModel->m_pBuffMat = m_pBuffMatAll[type];
	pModel->m_nNumMat = m_nNumMatAll[type];
	pModel->m_type = type;

	return pModel;
}