//=============================================================================
//
// camera.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

class CCamera
{
public:
	CCamera();							//�R���X�g���N�^
	~CCamera();							//�f�X�g���N�^
										
	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����
	void Set(void);						//�ݒ菈��

	const D3DXVECTOR3 GetRot(void);
	const D3DXVECTOR3 GetDirection(void);

	static CCamera* Create(D3DXVECTOR3 pos, D3DXVECTOR3 focalPoint);		//��������

private:

	D3DXVECTOR3 m_posV;						//���_
	D3DXVECTOR3 m_posR;						//�����_
	D3DXVECTOR3 m_DestPosV;					//�ړI�̎��_
	D3DXVECTOR3 m_DestPosR;					//�ړI�̒����_
	D3DXVECTOR3 m_vecU;						//������x�N�g��
	D3DXMATRIX  m_mtxProjection;			//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX  m_mtxView;					//�r���[�}�g���b�N�X
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_rotDest;					//�ړI�̌���
	float		m_fDistance;				//���_����v���C���[�܂ł̋���
	float		m_fDistanceFocalPoint;		//�����_����v���C���[�܂ł̋���
	float		m_fLenght;					//XZ�ʂ̎��_�ƒ����_�̊Ԃ̋���
	int			m_nDelay;					//

};

#endif // !_CAMERA_H_