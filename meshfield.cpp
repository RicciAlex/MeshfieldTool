//=============================================================================
//
// meshfield.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include <stdio.h>
#include "meshfield.h"
#include "application.h"
#include "rendering.h"
#include "object2D.h"
#include "inputKeyboard.h"
#include "debugProc.h"

float CMeshfield::m_fStaticSize = 100.0f;
CMeshfield* CMeshfield::m_pPresentField = nullptr;

//コンストラクタ
CMeshfield::CMeshfield()
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_nLineVertex = 0;
	m_nColumnVertex = 0;
	m_nUpdatingVtxIdx = 0;
	m_nLockedAxis = 0;
	m_bRead = false;
	m_bWire = false;
	m_bReturnToDefault = false;
	m_pPass = nullptr;
	m_fTextTiling = Vec2Null;
	m_fSavedValue = 0.0f;
	m_fSavedTexValue = 0.0f;

	m_pPresentField = this;
}

CMeshfield::CMeshfield(const int nPriority) : CObject::CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_nLineVertex = 0;
	m_nColumnVertex = 0;
	m_nUpdatingVtxIdx = 0;
	m_nLockedAxis = 1;
	m_bRead = false;
	m_bWire = false;
	m_bReturnToDefault = false;
	m_pPass = nullptr;
	m_fTextTiling = Vec2Null;
	m_fSavedValue = 0.0f;
	m_fSavedTexValue = 0.0f;

	m_pPresentField = this;
}

//デストラクタ
CMeshfield::~CMeshfield()
{

}

//初期化処理
HRESULT CMeshfield::Init(void)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = D3DXVECTOR2(50.0f, 50.0f);
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_nLineVertex = 0;
	m_nColumnVertex = 0;
	m_nUpdatingVtxIdx = 0;
	m_bRead = false;
	m_bWire = false;
	m_bReturnToDefault = false;
	m_pPass = nullptr;
	m_fTextTiling = D3DXVECTOR2(1.0f, 1.0f);
	m_fSavedValue = 0.0f;
	m_fSavedTexValue = 0.0f;

	return S_OK;
}

//終了処理
void CMeshfield::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}
}

//更新処理
void CMeshfield::Update(void)
{
	CApplication::MODE mode = CApplication::GetMode();

	if (mode == CApplication::MODE_FIELD)
	{
		if (!m_bReturnToDefault)
		{
			if (CInputKeyboard::GetKeyboardTrigger(DIK_L))
			{
				m_bWire = !m_bWire;
			}


			VERTEX_3D* pVtx = nullptr;

			WORD* pIdx = nullptr;

			//頂点バッファをロック
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			//インデックスバッファをロック
			m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

			for (int nCnt = 0; nCnt < m_nIndexNumber - 2; nCnt++)
			{
				if (pIdx[nCnt] != pIdx[nCnt + 1] && pIdx[nCnt] != pIdx[nCnt + 2] && pIdx[nCnt + 1] != pIdx[nCnt + 2])
				{
					D3DXVECTOR3 V1, V2, Norm, N;

					V1 = pVtx[pIdx[nCnt + 1]].pos - pVtx[pIdx[nCnt]].pos;
					V2 = pVtx[pIdx[nCnt + 2]].pos - pVtx[pIdx[nCnt + 1]].pos;


					if (nCnt % 2 == 0)
					{
						D3DXVec3Cross(&Norm, &V1, &V2);
					}
					else
					{
						D3DXVec3Cross(&Norm, &V2, &V1);
					}

					D3DXVec3Normalize(&Norm, &Norm);

					N = pVtx[pIdx[nCnt]].nor + Norm;
					//D3DXVec3Normalize(&N, &N);
					pVtx[pIdx[nCnt]].nor = N;
					N = pVtx[pIdx[nCnt + 1]].nor + Norm;
					//D3DXVec3Normalize(&N, &N);
					pVtx[pIdx[nCnt + 1]].nor = N;
					N = pVtx[pIdx[nCnt + 2]].nor + Norm;
					//D3DXVec3Normalize(&N, &N);
					pVtx[pIdx[nCnt + 2]].nor = N;
				}
			}

			//インデックスバッファをアンロック
			m_pIdxBuff->Unlock();

			//頂点バッファのアンロック
			m_pVtxBuff->Unlock();

			pVtx = nullptr;

			//頂点バッファをロック
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
			{
				D3DXVECTOR3 N = pVtx[nCnt].nor;
				D3DXVec3Normalize(&N, &N);
				pVtx[nCnt].nor = N;
			}

			if (CInputKeyboard::GetKeyboardTrigger(DIK_LEFT))
			{
				if (m_nUpdatingVtxIdx % m_nLineVertex > 0)
				{
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					m_nUpdatingVtxIdx--;
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else
				{
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					m_nUpdatingVtxIdx += (m_nLineVertex - 1);
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
			else if (CInputKeyboard::GetKeyboardTrigger(DIK_RIGHT))
			{
				if (m_nUpdatingVtxIdx % m_nLineVertex < m_nLineVertex - 1)
				{
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					m_nUpdatingVtxIdx++;
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else
				{
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					m_nUpdatingVtxIdx -= (m_nLineVertex - 1);
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
			else if (CInputKeyboard::GetKeyboardTrigger(DIK_UP))
			{
				if (m_nUpdatingVtxIdx - m_nLineVertex >= 0)
				{
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					m_nUpdatingVtxIdx -= m_nLineVertex;
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else
				{
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					m_nUpdatingVtxIdx += m_nVertexNumber;
					m_nUpdatingVtxIdx -= (m_nLineVertex);
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}
			else if (CInputKeyboard::GetKeyboardTrigger(DIK_DOWN))
			{
				if (m_nUpdatingVtxIdx + m_nLineVertex < m_nVertexNumber)
				{
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					m_nUpdatingVtxIdx += m_nLineVertex;
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
				else
				{
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					m_nUpdatingVtxIdx -= m_nVertexNumber;
					m_nUpdatingVtxIdx += (m_nLineVertex);
					pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				}
			}

			if (CInputKeyboard::GetKeyboardPress(DIK_Y))
			{
				if (m_nLockedAxis == 0)
				{
					pVtx[m_nUpdatingVtxIdx].pos.x += 1.0f;
				}
				else if (m_nLockedAxis == 1)
				{
					pVtx[m_nUpdatingVtxIdx].pos.y += 1.0f;
				}
				else
				{
					pVtx[m_nUpdatingVtxIdx].pos.z += 1.0f;
				}
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_H))
			{
				if (m_nLockedAxis == 0)
				{
					pVtx[m_nUpdatingVtxIdx].pos.x -= 1.0f;
				}
				else if (m_nLockedAxis == 1)
				{
					pVtx[m_nUpdatingVtxIdx].pos.y -= 1.0f;
				}
				else
				{
					pVtx[m_nUpdatingVtxIdx].pos.z -= 1.0f;
				}
			}
			if (CInputKeyboard::GetKeyboardPress(DIK_U))
			{
				pVtx[m_nUpdatingVtxIdx].tex.x += 0.001f;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_J))
			{
				pVtx[m_nUpdatingVtxIdx].tex.x -= 0.001f;
			}
			if (CInputKeyboard::GetKeyboardPress(DIK_I))
			{
				pVtx[m_nUpdatingVtxIdx].tex.y += 0.001f;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_K))
			{
				pVtx[m_nUpdatingVtxIdx].tex.y -= 0.001f;
			}

			if (CInputKeyboard::GetKeyboardPress(DIK_R))
			{
				for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
				{
					if (m_nLockedAxis == 0)
					{
						m_bReturnToDefault = true;
					}
					else if (m_nLockedAxis == 1)
					{
						pVtx[nCnt].pos.y = m_pos.y;
					}
					else
					{
						m_bReturnToDefault = true;
					}
				}
			}
			if (CInputKeyboard::GetKeyboardTrigger(DIK_Q))
			{
				m_nLockedAxis++;

				if (m_nLockedAxis > 2)
				{
					m_nLockedAxis = 0;
				}
			}

			if (CInputKeyboard::GetKeyboardPress(DIK_F2))
			{
				pVtx[m_nUpdatingVtxIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				FILE*pFile;				//ファイルポインタを宣言する

										//ファイルを開く
				pFile = fopen("data\\FieldData\\VMeshData.txt", "w");

				if (pFile != NULL)
				{//ファイルが開けた場合

					fprintf(pFile, "%d %d %d\n\n", m_nVertexNumber, m_nColumnVertex, m_nLineVertex);

					for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
					{
						D3DXCOLOR col = pVtx[nCnt].col;

						fprintf(pFile, "%f %f %f\n%f %f %f\n%f %f %f %f\n%f %f\n\n", pVtx[nCnt].pos.x, pVtx[nCnt].pos.y, pVtx[nCnt].pos.z, pVtx[nCnt].nor.x, pVtx[nCnt].nor.y, pVtx[nCnt].nor.z, col.r, col.g, col.b, col.a, pVtx[nCnt].tex.x, pVtx[nCnt].tex.y);
					}

					//ファイルを閉じる
					fclose(pFile);
				}
			}

			if (CInputKeyboard::GetKeyboardTrigger(DIK_C))
			{
				if (m_nLockedAxis == 0)
				{
					m_fSavedValue = pVtx[m_nUpdatingVtxIdx].pos.x;
				}
				else if (m_nLockedAxis == 1)
				{
					m_fSavedValue = pVtx[m_nUpdatingVtxIdx].pos.y;
				}
				else
				{
					m_fSavedValue = pVtx[m_nUpdatingVtxIdx].pos.z;
				}
			}
			else if (CInputKeyboard::GetKeyboardTrigger(DIK_V))
			{
				if (m_nLockedAxis == 0)
				{
					pVtx[m_nUpdatingVtxIdx].pos.x = m_fSavedValue;
				}
				else if (m_nLockedAxis == 1)
				{
					pVtx[m_nUpdatingVtxIdx].pos.y = m_fSavedValue;
				}
				else
				{
					pVtx[m_nUpdatingVtxIdx].pos.z = m_fSavedValue;
				}
			}

			if (CInputKeyboard::GetKeyboardTrigger(DIK_NUMPAD1))
			{
				m_fSavedTexValue = pVtx[m_nUpdatingVtxIdx].tex.x;
			}
			else if (CInputKeyboard::GetKeyboardTrigger(DIK_NUMPAD2))
			{
				pVtx[m_nUpdatingVtxIdx].tex.x = m_fSavedTexValue;
			}

			if (CInputKeyboard::GetKeyboardTrigger(DIK_NUMPAD4))
			{
				m_fSavedTexValue = pVtx[m_nUpdatingVtxIdx].tex.y;
			}
			else if (CInputKeyboard::GetKeyboardTrigger(DIK_NUMPAD5))
			{
				pVtx[m_nUpdatingVtxIdx].tex.y = m_fSavedTexValue;
			}

			//頂点バッファのアンロック
			m_pVtxBuff->Unlock();

			CDebugProc::Print("\n\n AddLine 0(down) / 9(up)");
			CDebugProc::Print("\n AddColumn 8(right) / 7(left)");
			CDebugProc::Print("\n\n CutLine 5(down) / 6(up)");
			CDebugProc::Print("\n CutColumn 3(right) / 4(left)");

			CDebugProc::Print("\n\n Selected Vertex: %d", m_nUpdatingVtxIdx);
			CDebugProc::Print("\n Move Coordinates: Y-H");

			char* pString = {};

			if (m_nLockedAxis == 0)
			{
				pString = "\n Locked Axis: X";
			}
			else if (m_nLockedAxis == 1)
			{
				pString = "\n Locked Axis: Y";
			}
			else
			{
				pString = "\n Locked Axis: Z";
			}

			CDebugProc::Print(pString);
			CDebugProc::Print("\n Change Axis: Q");

			CDebugProc::Print("\n Move Texture X Coordinates: U-J");
			CDebugProc::Print("\n Move Texture Y Coordinates: I-K");

			CDebugProc::Print("\n Save Mesh: F2");

			CDebugProc::Print("\n\n Copy Locked Coordinate : C (%f)\n Paste Locked Coordinate : V", m_fSavedValue);

			CDebugProc::Print("\n\n Copy Locked Tex X Coordinate : Numpad 1 (%f)\n Paste Locked Tex X Coordinate : Numpad 2", m_fSavedTexValue);
			CDebugProc::Print("\n\n Copy Locked Tex Y Coordinate : Numpad 4 (%f)\n Paste Locked Tex Y Coordinate : Numpad 5", m_fSavedTexValue);
		}
		else
		{
			CDebugProc::Print("\n Cancel: Backspace");
			CDebugProc::Print("\n Select Cell Size: %f", m_fStaticSize);
			CDebugProc::Print("\n Confirm: Enter");

			if (CInputKeyboard::GetKeyboardTrigger(DIK_BACKSPACE))
			{
				m_fStaticSize = 100.0f;
				m_bReturnToDefault = false;
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT))
			{
				if (m_fStaticSize < 5000.0f)
				{
					m_fStaticSize += 1.0f;
				}
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_LEFT))
			{
				if (m_fStaticSize > 0.0f)
				{
					m_fStaticSize -= 1.0f;
				}
			}
			else if (CInputKeyboard::GetKeyboardPress(DIK_RETURN))
			{
				VERTEX_3D* pVtx = nullptr;

				//頂点バッファをロック
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
				{
					D3DXVECTOR3 p = pVtx[nCnt].pos;

					if (m_nLockedAxis == 0)
					{
						pVtx[nCnt].pos = D3DXVECTOR3((nCnt % m_nLineVertex) * m_fStaticSize, p.y, p.z);
					}
					else
					{
						pVtx[nCnt].pos = D3DXVECTOR3(p.x, p.y, -1.0f * (nCnt / m_nLineVertex) * m_fStaticSize);
						int a = 0;
					}
				}

				m_fStaticSize = 100.0f;
				m_bReturnToDefault = false;

				m_pVtxBuff->Unlock();
			}
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_0))
		{
			AddLine(true);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_9))
		{
			AddLine(false);
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_8))
		{
			AddColumn(true);
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_7))
		{
			AddColumn(false);
		}

		if (m_nColumnVertex > 2)
		{
			if (CInputKeyboard::GetKeyboardTrigger(DIK_5))
			{
				CutLine(true);
			}
			if (CInputKeyboard::GetKeyboardTrigger(DIK_6))
			{
				CutLine(false);
			}
		}

		if (m_nLineVertex > 2)
		{
			if (CInputKeyboard::GetKeyboardTrigger(DIK_3))
			{
				CutColumn(true);
			}
			if (CInputKeyboard::GetKeyboardTrigger(DIK_4))
			{
				CutColumn(false);
			}
		}
	}
}

//描画処理
void CMeshfield::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans;											//計算用マトリックス

	void* p = this;

	if (m_bWire)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	//ワルドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワルドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画処理
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 14, 0, m_nPolygonNumber);

	pDevice->SetTexture(0, NULL);

	if (m_bWire)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//位置の設定処理
void CMeshfield::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの取得処理
const D3DXVECTOR2 CMeshfield::GetSize(void)
{
	return m_size;
}

//位置の取得処理
const D3DXVECTOR3 CMeshfield::GetPos(void)
{
	return m_pos;
}

//テクスチャの設定処理
void CMeshfield::SetTexture(CObject::TextType texture)
{
	LPDIRECT3DTEXTURE9 text = CObject_2D::GetTexturePointer(texture);
	m_pTexture = text;
}

void CMeshfield::SetTextureTiling(D3DXVECTOR2 TileSize)
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx = NULL;

	m_fTextTiling = TileSize;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (TileSize.x * (nCnt % m_nColumnVertex)), 0.0f + (TileSize.y * (nCnt / m_nColumnVertex)));
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

void CMeshfield::SetTextureTiling(float fTileSize)
{
	//頂点情報へのポインタ
	VERTEX_3D*pVtx = NULL;

	m_fTextTiling = D3DXVECTOR2(fTileSize, fTileSize);

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		//テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (fTileSize * (nCnt % m_nLineVertex)), 0.0f + (fTileSize * (nCnt / m_nLineVertex)));
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}







void CMeshfield::AddLine(const bool bBottom)
{
	VERTEX_3D* pVtx = nullptr;
	std::vector <D3DXVECTOR3> vPos;
	D3DXVECTOR3 VtxPos;
	vPos.clear();

	D3DXVECTOR3 pos = m_pPresentField->m_pos;
	D3DXVECTOR3 rot = m_pPresentField->m_rot;
	D3DXVECTOR2 size = m_pPresentField->m_size;
	D3DXVECTOR2 textTile = m_pPresentField->m_fTextTiling;
	int nLine = m_pPresentField->m_nColumnVertex;
	int nColumn = m_pPresentField->m_nLineVertex;
	int nVtxNum = (nColumn) * (nLine + 1);

	m_pPresentField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fN = 0.0f;

	if (!bBottom)
	{
		for (int nCnt = 0; nCnt < m_pPresentField->m_nLineVertex; nCnt++)
		{
			VtxPos = pVtx[nCnt].pos;
			//VtxPos.y = m_pPresentField->m_pos.y;
			vPos.push_back(VtxPos);
		}
		pos.z += size.y;

		fN = m_pPresentField->m_size.y;
	}

	for (int nCnt = 0; nCnt < m_pPresentField->m_nVertexNumber; nCnt++)
	{
		VtxPos = pVtx[nCnt].pos;
		VtxPos.z -= fN;
		vPos.push_back(VtxPos);
	}

	if (bBottom)
	{
		for (int nCnt = 0; nCnt < m_pPresentField->m_nLineVertex; nCnt++)
		{
			VtxPos = pVtx[m_pPresentField->m_nVertexNumber - m_pPresentField->m_nLineVertex + nCnt].pos;
			VtxPos.z -= m_pPresentField->m_size.y;
			vPos.push_back(VtxPos);
		}
	}

	//頂点バッファのアンロック
	m_pPresentField->m_pVtxBuff->Unlock();

	m_pPresentField->Release();

	m_pPresentField = CMeshfield::Create(pos, rot, size, nColumn - 1, nLine, 2);

	pVtx = nullptr;

	m_pPresentField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_pPresentField->m_nVertexNumber; nCnt++)
	{
		pVtx[nCnt].pos = vPos.data()[nCnt];
		pVtx[nCnt].tex = D3DXVECTOR2(textTile.x * (nCnt % m_pPresentField->m_nLineVertex), textTile.y * (nCnt / m_pPresentField->m_nLineVertex));
	}

	m_pPresentField->m_fTextTiling = textTile;

	//頂点バッファのアンロック
	m_pPresentField->m_pVtxBuff->Unlock();

	vPos.clear();
}


void CMeshfield::AddColumn(const bool bRight)
{
	VERTEX_3D* pVtx = nullptr;
	std::vector <D3DXVECTOR3> vPos;
	D3DXVECTOR3 VtxPos;
	vPos.clear();

	D3DXVECTOR3 pos = m_pPresentField->m_pos;
	D3DXVECTOR3 rot = m_pPresentField->m_rot;
	D3DXVECTOR2 size = m_pPresentField->m_size;
	D3DXVECTOR2 textTile = m_pPresentField->m_fTextTiling;
	int nLine = m_pPresentField->m_nColumnVertex;
	int nColumn = m_pPresentField->m_nLineVertex;
	int nVtxNum = (nColumn + 1) * (nLine);

	m_pPresentField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fX = 0.0f;

	if (!bRight)
	{
		fX = size.x;
	}

	for (int nCnt = 0; nCnt < nVtxNum; nCnt++)
	{
		if (!bRight)
		{
			if (nCnt % nColumn == 0)
			{
				VtxPos = pVtx[nCnt].pos;
				vPos.push_back(VtxPos);
			}
		}

		VtxPos = pVtx[nCnt].pos;
		VtxPos.x += fX;
		vPos.push_back(VtxPos);

		if (bRight)
		{
			if (nCnt % (nColumn) == nColumn - 1)
			{
				VtxPos = pVtx[nCnt].pos;
				VtxPos.x += size.x;
				vPos.push_back(VtxPos);
			}
		}
	}

	//頂点バッファのアンロック
	m_pPresentField->m_pVtxBuff->Unlock();

	if (!bRight)
	{
		pos.x -= size.x;
	}

	m_pPresentField->Release();

	m_pPresentField = CMeshfield::Create(pos, rot, size, nColumn, nLine - 1, 2);

	pVtx = nullptr;

	m_pPresentField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_pPresentField->m_nVertexNumber; nCnt++)
	{
		pVtx[nCnt].pos = vPos.data()[nCnt];
		pVtx[nCnt].tex = D3DXVECTOR2(textTile.x * (nCnt % m_pPresentField->m_nLineVertex), textTile.y * (nCnt / m_pPresentField->m_nLineVertex));
	}

	m_pPresentField->m_fTextTiling = textTile;

	//頂点バッファのアンロック
	m_pPresentField->m_pVtxBuff->Unlock();

	vPos.clear();
}


void CMeshfield::CutLine(const bool bBottom)
{
	VERTEX_3D* pVtx = nullptr;
	std::vector <D3DXVECTOR3> vPos;
	D3DXVECTOR3 VtxPos;
	vPos.clear();

	D3DXVECTOR3 pos = m_pPresentField->m_pos;
	D3DXVECTOR3 rot = m_pPresentField->m_rot;
	D3DXVECTOR2 size = m_pPresentField->m_size;
	D3DXVECTOR2 textTile = m_pPresentField->m_fTextTiling;
	int nLine = m_pPresentField->m_nColumnVertex;
	int nColumn = m_pPresentField->m_nLineVertex;
	int nVtxNum = (nColumn) * (nLine - 1);

	m_pPresentField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (!bBottom)
	{
		for (int nCnt = m_pPresentField->m_nLineVertex; nCnt < m_pPresentField->m_nVertexNumber; nCnt++)
		{
			VtxPos = pVtx[nCnt].pos;
			VtxPos.z += size.y;
			vPos.push_back(VtxPos);
		}
		pos.z -= size.y;
	}
	else
	{
		for (int nCnt = 0; nCnt < nVtxNum; nCnt++)
		{
			VtxPos = pVtx[nCnt].pos;
			vPos.push_back(VtxPos);
		}
	}

	//頂点バッファのアンロック
	m_pPresentField->m_pVtxBuff->Unlock();

	m_pPresentField->Release();

	m_pPresentField = CMeshfield::Create(pos, rot, size, nColumn - 1, nLine - 2, 2);

	pVtx = nullptr;

	m_pPresentField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_pPresentField->m_nVertexNumber; nCnt++)
	{
		pVtx[nCnt].pos = vPos.data()[nCnt];
		pVtx[nCnt].tex = D3DXVECTOR2(textTile.x * (nCnt % m_pPresentField->m_nLineVertex), textTile.y * (nCnt / m_pPresentField->m_nLineVertex));
	}

	m_pPresentField->m_fTextTiling = textTile;

	//頂点バッファのアンロック
	m_pPresentField->m_pVtxBuff->Unlock();

	vPos.clear();
}

void CMeshfield::CutColumn(const bool bRight)
{
	VERTEX_3D* pVtx = nullptr;
	std::vector <D3DXVECTOR3> vPos;
	D3DXVECTOR3 VtxPos;
	vPos.clear();

	D3DXVECTOR3 pos = m_pPresentField->m_pos;
	D3DXVECTOR3 rot = m_pPresentField->m_rot;
	D3DXVECTOR2 size = m_pPresentField->m_size;
	D3DXVECTOR2 textTile = m_pPresentField->m_fTextTiling;
	int nLine = m_pPresentField->m_nColumnVertex;
	int nColumn = m_pPresentField->m_nLineVertex;
	int nVtxNum = (nColumn - 1) * (nLine);

	m_pPresentField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fX = 0.0f;

	if (!bRight)
	{
		fX = size.x;
	}

	for (int nCnt = 0; nCnt < m_pPresentField->m_nVertexNumber; nCnt++)
	{
		if (!bRight)
		{
			if (nCnt % nColumn != 0)
			{
				VtxPos = pVtx[nCnt].pos;
				VtxPos.x -= fX;
				vPos.push_back(VtxPos);
			}
		}

		if (bRight)
		{
			if (nCnt % (nColumn) != nColumn - 1)
			{
				VtxPos = pVtx[nCnt].pos;
				VtxPos.x += fX;
				vPos.push_back(VtxPos);
			}
		}
	}

	//頂点バッファのアンロック
	m_pPresentField->m_pVtxBuff->Unlock();

	if (!bRight)
	{
		pos.x += size.x;
	}

	m_pPresentField->Release();

	m_pPresentField = CMeshfield::Create(pos, rot, size, nColumn - 2, nLine - 1, 2);

	pVtx = nullptr;

	m_pPresentField->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_pPresentField->m_nVertexNumber; nCnt++)
	{
		pVtx[nCnt].pos = vPos.data()[nCnt];
		pVtx[nCnt].tex = D3DXVECTOR2(textTile.x * (nCnt % m_pPresentField->m_nLineVertex), textTile.y * (nCnt / m_pPresentField->m_nLineVertex));
	}

	m_pPresentField->m_fTextTiling = textTile;

	//頂点バッファのアンロック
	m_pPresentField->m_pVtxBuff->Unlock();

	vPos.clear();
}


CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 unitSize, const int nColumn, const int nLine)
{
	CMeshfield* pField = new CMeshfield(3);

	if (FAILED(pField->Init()))
	{
		return nullptr;
	}

	pField->m_pos = pos;
	pField->m_rot = rot;
	pField->m_size = unitSize;
	pField->m_nColumnVertex = nLine + 1;
	pField->m_nLineVertex = nColumn + 1;
	pField->SetVertex();

	return pField;
}

CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR2 unitSize, const int nColumn, const int nLine, const int nPriority)
{
	CMeshfield* pField = new CMeshfield(nPriority);

	if (FAILED(pField->Init()))
	{
		return nullptr;
	}

	pField->m_pos = pos;
	pField->m_rot = rot;
	pField->m_size = unitSize;
	pField->m_nColumnVertex = nLine + 1;
	pField->m_nLineVertex = nColumn + 1;
	pField->SetVertex();

	return pField;
}

//生成処理
CMeshfield* CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, char* pPass, const int nPriority)
{
	CMeshfield* pField = new CMeshfield(nPriority);

	if (FAILED(pField->Init()))
	{
		return nullptr;
	}

	pField->m_pos = pos;
	pField->m_rot = rot;
	pField->m_pPass = pPass;
	pField->LoadVertex();

	return pField;
}







//頂点インデックスの設定処理
void CMeshfield::SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//デバイスの取得

	//頂点数の計算
	m_nVertexNumber = m_nLineVertex * m_nColumnVertex;
	////ポリゴン数の計算
	//m_nPolygonNumber = (((((m_nColumnVertex - 1) * 2) + 2) * 2) + ((((m_nColumnVertex - 1) * 2) + 4) * ((m_nLineVertex - 1) - 2)));
	////インデックス数の計算
	//m_nIndexNumber = m_nPolygonNumber + 2;
	m_nIndexNumber = ((m_nLineVertex * 2) * (m_nColumnVertex - 1)) + (2 * (m_nColumnVertex - 2));
	m_nPolygonNumber = m_nIndexNumber - 2;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexNumber,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndexNumber,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx = nullptr;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点情報の設定
	for (int nCnt = 0; nCnt < m_nVertexNumber; nCnt++)
	{
		//頂点の位置の初期化
		pVtx[nCnt].pos = D3DXVECTOR3((float)(m_size.x * (nCnt % m_nLineVertex)), 0.0f, (float)(-m_size.y * (nCnt / m_nLineVertex)));
		//頂点の法線の初期化
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//頂点カラーの初期化
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (1.0f * (nCnt % m_nLineVertex)), 0.0f + (1.0f * (nCnt / m_nLineVertex)));
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	WORD*pIdx;		//インデックス情報へのポインタ

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nStart = 0;		//計算用のローカル変数
	int nCtrl = 0;

	for (int Z = 0; Z < m_nColumnVertex - 1; Z++)
	{
		for (int X = 0; X < m_nLineVertex; X++)
		{
			int a = ((Z + 1) * m_nLineVertex) + (X), b = ((Z)* m_nLineVertex) + (X);

			pIdx[nCtrl + 0] = a;
			pIdx[nCtrl + 1] = b;

			nCtrl += 2;
			nStart++;

			if (nStart == m_nLineVertex && Z < m_nColumnVertex - 2)
			{
				a = ((Z + 2) * m_nLineVertex);
				pIdx[nCtrl + 0] = b;
				pIdx[nCtrl + 1] = a;

				nCtrl += 2;
				nStart = 0;
			}
		}
	}

	m_pIdxBuff->Unlock();

	m_pPresentField->SetTexture(CObject::TEXTURE_BLOCK);
}

//頂点インデックスのロード処理
void CMeshfield::LoadVertex(void)
{
	FILE*pFile;				//ファイルポインタを宣言する

	int nVtxNum = 0;
	int nLine = 0;
	int nColumn = 0;

	//ファイルを開く
	pFile = fopen(m_pPass, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
	 //ファイルにランキング情報を読み込む

		fscanf(pFile, "%d", &nVtxNum);
		fscanf(pFile, "%d", &nColumn);
		fscanf(pFile, "%d", &nLine);

		m_nVertexNumber = nVtxNum;
		m_nLineVertex = nLine;
		m_nColumnVertex = nColumn;

	//ポリゴン数の計算
		m_nIndexNumber = ((m_nLineVertex * 2) * (m_nColumnVertex - 1)) + (2 * (m_nColumnVertex - 2));
		m_nPolygonNumber = m_nIndexNumber - 2;

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexNumber,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndexNumber,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx = nullptr;

	std::vector <VERTEX_3D> vVtx;
	vVtx.clear();

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < nVtxNum; nCnt++)
	{

		fscanf(pFile, "%f", &pVtx[nCnt].pos.x);
		fscanf(pFile, "%f", &pVtx[nCnt].pos.y);
		fscanf(pFile, "%f", &pVtx[nCnt].pos.z);

		fscanf(pFile, "%f", &pVtx[nCnt].nor.x);
		fscanf(pFile, "%f", &pVtx[nCnt].nor.y);
		fscanf(pFile, "%f", &pVtx[nCnt].nor.z);

		D3DXCOLOR col = ColorNull;

		fscanf(pFile, "%f", &col.r);
		fscanf(pFile, "%f", &col.g);
		fscanf(pFile, "%f", &col.b);
		fscanf(pFile, "%f", &col.a);

		pVtx[nCnt].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

		float x = 0.0f;
		float y = 0.0f;

		fscanf(pFile, "%f", &x);
		fscanf(pFile, "%f", &y);

		pVtx[nCnt].tex = D3DXVECTOR2(x, y);

	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//ファイルを閉じる
	fclose(pFile);

	}
	else
	{//ファイルが開けなかった場合
		Release();
		return;
	}

	WORD*pIdx;		//インデックス情報へのポインタ

					//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nStart = 0;		//計算用のローカル変数
	int nCtrl = 0;

	for (int Z = 0; Z < m_nColumnVertex - 1; Z++)
	{
		for (int X = 0; X < m_nLineVertex; X++)
		{
			int a = ((Z + 1) * m_nLineVertex) + (X), b = ((Z)* m_nLineVertex) + (X);

			pIdx[nCtrl + 0] = a;
			pIdx[nCtrl + 1] = b;

			nCtrl += 2;
			nStart++;

			if (nStart == m_nLineVertex && Z < m_nColumnVertex - 2)
			{
				a = ((Z + 2) * m_nLineVertex);
				pIdx[nCtrl + 0] = b;
				pIdx[nCtrl + 1] = a;

				nCtrl += 2;
				nStart = 0;
			}
		}
	}

	m_pIdxBuff->Unlock();

}