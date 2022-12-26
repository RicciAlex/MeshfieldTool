//=============================================================================
//
// object.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include "object2D.h"
#include <random>

//=============================================================================
//静的メンバー変数の宣言 
//=============================================================================
//int CObject::m_nNumAll = 0;										//存在するポリゴン数
//CObject* CObject::m_pObject[CObject::MaxObject] = {};			//オブジェクトへのポンタ
//int CObject::m_nPriorityObjNum[CObject::Max_Priority] = {};
bool CObject::m_bPause = false;
CObject* CObject::m_pTop[CObject::Max_Priority] = {};
CObject* CObject::m_pCurrent[CObject::Max_Priority] = {};

//=============================================================================
//コンストラクタ
//=============================================================================
CObject::CObject()
{
	if (m_pCurrent[2] != nullptr)
	{
		m_pCurrent[2]->m_pNext = this;
		m_pPrev = m_pCurrent[2];
		m_pCurrent[2] = this;
	}
	else
	{
		m_pTop[2] = this;
		m_pCurrent[2] = this;
		m_pPrev = nullptr;
	}

	m_pNext = nullptr;

	m_nPriority = 3;
	m_bDeath = false;
}

CObject::CObject(int nPriority)
{
	if (m_pCurrent[nPriority - 1] != nullptr)
	{//オブジェクト既に存在する場合
		m_pCurrent[nPriority - 1]->m_pNext = this;
		m_pPrev = m_pCurrent[nPriority - 1];
		m_pCurrent[nPriority - 1] = this;
	}
	else
	{//これは最初のオブジェクトだったら
		m_pTop[nPriority - 1] = this;
		m_pCurrent[nPriority - 1] = this;
		m_pPrev = nullptr;
	}

	m_pNext = nullptr;

	m_nPriority = nPriority;
}

//=============================================================================
//デストラクタ
//=============================================================================
CObject::~CObject()
{

}

//オブジェクトを消す処理
void CObject::Release(void)
{
	//if (m_pPrev != nullptr)
	//{
	//	if (m_pNext != nullptr)
	//	{//リストの中だったら
	//		m_pPrev->m_pNext = m_pNext;
	//		m_pNext->m_pPrev = m_pPrev;
	//	}
	//	else
	//	{//リストの最後のオブジェクトだったら
	//		m_pPrev->m_pNext = nullptr;
	//		m_pCurrent[m_nPriority - 1] = m_pPrev;
	//	}
	//}
	//else
	//{
	//	if (m_pNext != nullptr)
	//	{//リストの最初のオブジェクトだったら
	//		m_pNext->m_pPrev = nullptr;
	//		m_pTop[m_nPriority - 1] = m_pNext;
	//	}
	//	else
	//	{//このオブジェクトしかない場合
	//		m_pTop[m_nPriority - 1] = nullptr;
	//		m_pCurrent[m_nPriority - 1] = nullptr;
	//	}
	//}

	Uninit();
	m_bDeath = true;
}

void CObject::SetPriority(int nPriority)
{
	if (nPriority < 1)
	{
		nPriority = 1;
	}
	else if(nPriority > 5)
	{
		nPriority = 5;
	}

	int nLastPriority = m_nPriority;

	if (m_pPrev != nullptr)
	{
		if (m_pNext != nullptr)
		{
			m_pPrev->m_pNext = m_pNext;
			m_pNext->m_pPrev = m_pPrev;
		}
		else
		{
			m_pPrev->m_pNext = nullptr;
			m_pCurrent[m_nPriority - 1] = m_pPrev;
		}
	}
	else
	{
		if (m_pNext != nullptr)
		{
			m_pNext->m_pPrev = nullptr;
			m_pTop[m_nPriority - 1] = m_pNext;
		}
		else
		{
			m_pTop[m_nPriority - 1] = nullptr;
			m_pCurrent[m_nPriority - 1] = nullptr;
		}
	}

	m_nPriority = nPriority;

	if (m_pCurrent[nPriority - 1] != nullptr)
	{
		m_pCurrent[nPriority - 1]->m_pNext = this;
		m_pPrev = m_pCurrent[nPriority - 1];
		m_pCurrent[nPriority - 1] = this;
	}
	else
	{
		m_pTop[nPriority - 1] = this;
		m_pCurrent[nPriority - 1] = this;
		m_pPrev = nullptr;
	}

	m_pNext = nullptr;
}

//===============================================================================
//
//								静的関数
//
//===============================================================================

//=============================================================================
//全部の終了処理
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject* pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{
				CObject* pNext = pCurrent->m_pNext;

				if (pCurrent->m_pPrev != nullptr)
				{
					if (pCurrent->m_pNext != nullptr)
					{//リストの中だったら
						pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
						pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
					}
					else
					{//リストの最後のオブジェクトだったら
						pCurrent->m_pPrev->m_pNext = nullptr;
						m_pCurrent[pCurrent->m_nPriority - 1] = pCurrent->m_pPrev;
					}
				}
				else
				{
					if (pCurrent->m_pNext != nullptr)
					{//リストの最初のオブジェクトだったら
						pCurrent->m_pNext->m_pPrev = nullptr;
						m_pTop[pCurrent->m_nPriority - 1] = pCurrent->m_pNext;
					}
					else
					{//このオブジェクトしかない場合
						m_pTop[pCurrent->m_nPriority - 1] = nullptr;
						m_pCurrent[pCurrent->m_nPriority - 1] = nullptr;
					}
				}

				pCurrent->Uninit();
				delete pCurrent;

				pCurrent = pNext;
			}
		}
	}
}

//=============================================================================
//全部の更新処理
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject* pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{
				CObject* pNext = pCurrent->m_pNext;

				if (!pCurrent->m_bDeath)
				{
					pCurrent->Update();
				}
				pCurrent = pNext;
			}
		}
	}

	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject* pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{

				CObject* pNext = pCurrent->m_pNext;

				if (pCurrent->m_bDeath)
				{
					if (pCurrent->m_pPrev != nullptr)
					{
						if (pCurrent->m_pNext != nullptr)
						{//リストの中だったら
							pCurrent->m_pPrev->m_pNext = pCurrent->m_pNext;
							pCurrent->m_pNext->m_pPrev = pCurrent->m_pPrev;
						}
						else
						{//リストの最後のオブジェクトだったら
							pCurrent->m_pPrev->m_pNext = nullptr;
							m_pCurrent[pCurrent->m_nPriority - 1] = pCurrent->m_pPrev;
						}
					}
					else
					{
						if (pCurrent->m_pNext != nullptr)
						{//リストの最初のオブジェクトだったら
							pCurrent->m_pNext->m_pPrev = nullptr;
							m_pTop[pCurrent->m_nPriority - 1] = pCurrent->m_pNext;
						}
						else
						{//このオブジェクトしかない場合
							m_pTop[pCurrent->m_nPriority - 1] = nullptr;
							m_pCurrent[pCurrent->m_nPriority - 1] = nullptr;
						}
					}

					//pCurrent->Uninit();
					delete pCurrent;
				}

				pCurrent = pNext;
			}
		}
	}
}

//=============================================================================
//全部の描画処理
//=============================================================================
void CObject::DrawAll(void)
{
	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		if (m_pTop[nCnt] != nullptr)
		{
			CObject* pCurrent = m_pTop[nCnt];

			while (pCurrent != nullptr)
			{
				if (!pCurrent->m_bDeath)
				{
					pCurrent->Draw();
				}

				pCurrent = pCurrent->m_pNext;
			}
		}
	}
}

//=============================================================================
//生成処理
//=============================================================================

//オブジェクトの取得処理
CObject** CObject::GetObj(void)
{
	return &m_pTop[0];
}

void CObject::SetPause(const bool bPause)
{
	m_bPause = bPause;
}

//当たり判定(丸)
bool CObject::CircleHit(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, float fRadius1, float fRadius2)
{
	float radius = (fRadius1 * fRadius1) + (fRadius2 * fRadius2);

	float deltaX = (pos2->x - pos1->x) * (pos2->x - pos1->x);
	float deltaY = (pos2->y - pos1->y) * (pos2->y - pos1->y);

	if (deltaX + deltaY <= radius)
	{
		return true;
	}

	return false;
}

bool CObject::CircleHit(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	float fRadius1 = 0.5f * ((size1.x) + (size1.y));
	float fRadius2 = 0.5f * ((size2.x) + (size2.y));

	float radius = (fRadius1 * fRadius1) + (fRadius2 * fRadius2);

	float deltaX = (pos2->x - pos1->x) * (pos2->x - pos1->x);
	float deltaY = (pos2->y - pos1->y) * (pos2->y - pos1->y);

	if ((deltaX + deltaY) <= radius)
	{
		return true;
	}

	return false;
}

//当たり判定(四角形)
bool CObject::HitBox(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	float top, bottom, right, left;
	left = pos2->x - (size1.x + size2.x);
	right = pos2->x + (size1.x + size2.x);
	top = pos2->y - (size1.y + size2.y);
	bottom = pos2->y + (size1.y + size2.y);

	if (pos1->x >= left && pos1->x <= right &&
		pos1->y >= top && pos1->y <= bottom)
	{
		return true;
	}

	return false;
}

D3DXVECTOR3 CObject::GetPerpendicularVersor(D3DXVECTOR3 V)
{
	D3DXVECTOR3 Result, Unit;
	float fHalfPi = D3DX_PI * 0.5f;

	Unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	if (V.y > Unit.y)
	{
		fHalfPi *= -1.0f;
	}

	D3DXVec3Normalize(&V, &V);

	float fDot = D3DXVec3Dot(&V, &Unit);

	float fAngle = (float)acos(fDot);

	Result = D3DXVECTOR3(cosf(fAngle + fHalfPi), sinf(fAngle + fHalfPi), 0.0f);

	return Result;
}

std::random_device rd;
std::mt19937 gen(rd());

int CObject::random(const int low, const int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}


void CObject::DebugDestroy(void)
{
	int a = random(0, 5);

	CObject* pObj = nullptr;

	while (pObj == nullptr)
	{
		pObj = m_pTop[random(0, 4)];
	}

	for (int nCnt = 0; nCnt < a; nCnt++)
	{
		if (pObj->m_pNext != nullptr)
		{
			pObj = pObj->m_pNext;
		}
	}

	if (pObj != nullptr)
	{
		pObj->Release();
	}
}