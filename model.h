//=============================================================================
//
// model.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MODEL_H
#define _MODEL_H

//=============================================================================
//�C���N���[�h�t�@�C��
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

	CModel();										//�R���X�g���N�^
	CModel(const int nPriority);					//�R���X�g���N�^
	virtual ~CModel() override;						//�f�X�g���N�^

	virtual HRESULT Init(void) override;						//����������
	virtual void Uninit(void) override;							//�I������
	virtual void Update(void) override;							//�X�V����
	virtual void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;
	const D3DXVECTOR3 GetPos(void) override;

	void SetRot(const D3DXVECTOR3 ros);
	const D3DXVECTOR3 GetRot(void);

	const D3DXVECTOR2 GetSize(void) override;										//�|���S���̃T�C�Y�̎擾����
	const ModelType GetType(void);

	static void LoadAllModels(void);
	static void DestroyAllModels(void);
	static void LoadSavedModels(void);
	static void AddModel(CModel* pModel);

	static void OutputModelData(void);

	static CModel* Create(ModelType type, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CModel* Create(ModelType type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, const int nPriority);

private:

	LPD3DXMESH		m_pMesh;					//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	m_pBuffMat;					//�}�e���A�����ւ̃|�C���^
	DWORD			m_nNumMat;					//�}�e���A�����̐�
	D3DXVECTOR3		m_pos;						//���݂̈ʒu
	D3DXVECTOR3		m_LastPos;					//�O��̈ʒu
	D3DXVECTOR3		m_move;						//���f���̈ړ���
	D3DXVECTOR3		m_rot;						//����
	D3DXVECTOR3		m_minCoord, m_maxCoord;		//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMATRIX		m_mtxWorld;					//���[���h�}�g���b�N�X
	ModelType		m_type;						//���f���̎��
												//D3DXVECTOR3		m_rotDestModel;					//�ړI�p�x
												//D3DXVECTOR3 Vtx[4];

	static LPD3DXMESH		m_pMeshAll[MODEL_MAX];					//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMatAll[MODEL_MAX];				//�}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMatAll[MODEL_MAX];					//�}�e���A�����̐�
	static char*			m_pModelPass[MODEL_MAX];					//���f���̑��΃p�X
	static std::vector <LPDIRECT3DTEXTURE9> m_vModelTexture[MODEL_MAX];		//���f���̃e�N�X�`���ւ̃|�C���^�̃x�N�g��

	static std::vector <CModel*> m_vModel;
};

#endif