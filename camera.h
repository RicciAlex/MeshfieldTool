//=============================================================================
//
// camera.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

class CCamera
{
public:
	CCamera();							//コンストラクタ
	~CCamera();							//デストラクタ
										
	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理
	void Set(void);						//設定処理

	const D3DXVECTOR3 GetRot(void);
	const D3DXVECTOR3 GetDirection(void);

	static CCamera* Create(D3DXVECTOR3 pos, D3DXVECTOR3 focalPoint);		//生成処理

private:

	D3DXVECTOR3 m_posV;						//視点
	D3DXVECTOR3 m_posR;						//注視点
	D3DXVECTOR3 m_DestPosV;					//目的の視点
	D3DXVECTOR3 m_DestPosR;					//目的の注視点
	D3DXVECTOR3 m_vecU;						//上方向ベクトル
	D3DXMATRIX  m_mtxProjection;			//プロジェクションマトリックス
	D3DXMATRIX  m_mtxView;					//ビューマトリックス
	D3DXVECTOR3 m_rot;						//向き
	D3DXVECTOR3 m_rotDest;					//目的の向き
	float		m_fDistance;				//視点からプレイヤーまでの距離
	float		m_fDistanceFocalPoint;		//注視点からプレイヤーまでの距離
	float		m_fLenght;					//XZ面の視点と注視点の間の距離
	int			m_nDelay;					//

};

#endif // !_CAMERA_H_