//=============================================================================
//
// modelCursor.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _MODEL_CURSOR_H_
#define _MODEL_CURSOR_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include "model.h"
#include <vector>

//=============================================================================
//�O���錾
//=============================================================================

class CModelCursor : public CObject
{
public:
	CModelCursor();
	~CModelCursor()override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;				//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;

	static CModelCursor* Create(CModel::ModelType type, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	void ChangeModel(void);

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	CModel::ModelType m_type;
	int m_nLockedAxis;
	float m_fUpdateSpeed;

	CModel* m_pModel;
};



#endif