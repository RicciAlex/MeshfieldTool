//=============================================================================
//
// directionalLight.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _DIRECTIONAL_LIGHT_H_
#define _DIRECTIONAL_LIGHT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "light.h"

class CDirectionalLight : public CLight
{
public:

	CDirectionalLight();					//�R���X�g���N�^
	~CDirectionalLight() override;			//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CDirectionalLight* Create(D3DXCOLOR col, D3DXVECTOR3 dir);		//��������

private:

	D3DLIGHT9 m_pDirLight;					//���C�g
};

#endif // !_DIRECTIONAL_LIGHT_H_