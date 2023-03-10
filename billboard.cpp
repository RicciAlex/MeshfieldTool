//=============================================================================
//
// billboard.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "billboard.h"
#include "application.h"
#include "rendering.h"
#include "object2D.h"

//コンストラクタ
CBillboard::CBillboard()
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_fFrameRot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
}

CBillboard::CBillboard(const int nPriority) : CObject::CObject(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_fFrameRot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);
}

//デストラクタ
CBillboard::~CBillboard()
{

}

//初期化処理
HRESULT CBillboard::Init(void)
{
	m_pVtxBuff = nullptr;
	m_pTexture = nullptr;

	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_fFrameRot = Vec3Null;
	m_size = Vec2Null;
	D3DXMatrixIdentity(&m_mtxWorld);

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			pVtx[nCnt].pos = Vec3Null;					//頂点座標の設定
			pVtx[nCnt].nor = Vec3Null;					//法線ベクトルの設定
			pVtx[nCnt].nor.y = 1.0f;					//法線ベクトルの設定
			pVtx[nCnt].col = ColorFull;					//頂点カラーの設定
		}

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//終了処理
void CBillboard::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}
}

//更新処理
void CBillboard::Update(void)
{

}

//描画処理
void CBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans;											//計算用マトリックス
	D3DXMATRIX mtxView;														//ビューマトリックス

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	/*pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);*/

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ワルドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._33 = mtxView._33;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワルドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//四角形を描画する
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//元の設定に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	/*pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);*/

	//テクスチャへのポインタをNULLにする
	pDevice->SetTexture(0, NULL);

}

//サイズの設定処理
void CBillboard::SetSize(const D3DXVECTOR2 size)
{
	m_size = size;

	//頂点情報へのポインタ
	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//位置の設定処理
void CBillboard::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの取得処理
const D3DXVECTOR2 CBillboard::GetSize(void)
{
	return m_size;
}

//位置の取得処理
const D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}

//テクスチャの種類の設定処理
void CBillboard::SetTexture(TextType textType)
{
	LPDIRECT3DTEXTURE9 text = CObject_2D::GetTexturePointer(textType);
	m_pTexture = text;														//テクスチャの種類の設定
}





//生成処理
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CBillboard* pObj = new CBillboard(3);

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	pObj->m_pos = pos;
	pObj->SetSize(size);

	return pObj;
}

//生成処理
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, const int nPriority)
{
	CBillboard* pObj = new CBillboard(nPriority);

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	pObj->m_pos = pos;
	pObj->SetSize(size);

	return pObj;
}