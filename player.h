//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CModel;

class CPlayer
{
public:
	CPlayer();											//�R���X�g���N�^
	~CPlayer();									//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos);				//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void);				//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void);

	D3DXVECTOR3 GetDestRot(void) { return m_DestRot; };

	static CPlayer* Create(const D3DXVECTOR3 pos);

private:

	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_move;									//���x
	D3DXVECTOR3 m_DestRot;

	CModel* m_pModel;									//���f��
};

#endif