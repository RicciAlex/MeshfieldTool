//=============================================================================
//
// model.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"
#include "application.h"
#include "object2D.h"
#include "rendering.h"
#include "modelCursor.h"
#include <string>

LPD3DXMESH		CModel::m_pMeshAll[MODEL_MAX] = {};					//���b�V�����ւ̃|�C���^
LPD3DXBUFFER	CModel::m_pBuffMatAll[MODEL_MAX] = {};				//�}�e���A�����ւ̃|�C���^
DWORD			CModel::m_nNumMatAll[MODEL_MAX] = {};				//�}�e���A�����̐�
std::vector <LPDIRECT3DTEXTURE9>     CModel::m_vModelTexture[CModel::MODEL_MAX];		//���f���̃e�N�X�`���ւ̃|�C���^�̃x�N�g��
std::vector <CModel*> CModel::m_vModel;

char*			CModel::m_pModelPass[MODEL_MAX] =
{
	{ "data\\MODELS\\Tear.x" },
	{ "data\\MODELS\\CrobatBody.x" },
	{ "data\\MODELS\\Tree.x" }
};

//�R���X�g���N�^
CModel::CModel()
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;								//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_JEWEL_TEAR;
}

CModel::CModel(const int nPriority) : CObject::CObject(nPriority)
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;								//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_type = CModel::MODEL_JEWEL_TEAR;
}

//�f�X�g���N�^
CModel::~CModel()
{

}

//����������
HRESULT CModel::Init(void)
{
	m_pMesh = nullptr;								//���b�V�����ւ̃|�C���^
	m_pBuffMat = nullptr;							//�}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;									//�}�e���A�����̐�
	m_pos = Vec3Null;								//���݂̈ʒu
	m_LastPos = Vec3Null;							//�O��̈ʒu
	m_move = Vec3Null;								//���f���̈ړ���
	m_rot = Vec3Null;								//����
	m_minCoord = Vec3Null;
	m_maxCoord = Vec3Null;							//���f���̒��_���W�̍ŏ��l�ƍő�l
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X

													/*std::vector <LPDIRECT3DTEXTURE9> v;

													v.clear();

													LPDIRECT3DTEXTURE9 pText = CObject_2D::GetTexturePointer(CObject::TextureNumbers);

													v.push_back(nullptr);
													v.push_back(pText);

													LPDIRECT3DTEXTURE9 a = v.data()[0];
													LPDIRECT3DTEXTURE9 b = v.data()[1];*/

	return S_OK;
}

//�I������
void CModel::Uninit(void)
{

}

//�X�V����
void CModel::Update(void)
{

}

//�`�揈��
void CModel::Draw(void)
{
	CApplication::MODE mode = CApplication::GetMode();

	if (mode == CApplication::MODE_MODEL)
	{
		LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
		D3DXMATRIX mtxRot, mtxTrans;							//�v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;									//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL *pMat;										//�}�e���A���f�[�^�ւ̃|�C���^

																//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

																//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_vModelTexture[m_type].data()[nCntMat]);

			//���f���p�[�c�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		//�ێ��������}�e���A����߂�
		pDevice->SetMaterial(&matDef);

		//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

//�ʒu�̐ݒ菈��
void CModel::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
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

//�|���S���̃T�C�Y�̎擾����
const D3DXVECTOR2 CModel::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

const CModel::ModelType CModel::GetType(void)
{
	return m_type;
}






//���f���S���̓ǂݍ��ݏ���
void CModel::LoadAllModels(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	for (int nCnt = 0; nCnt < CModel::MODEL_MAX; nCnt++)
	{
		m_vModelTexture[nCnt].clear();

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_pModelPass[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatAll[nCnt],
			NULL,
			&m_nNumMatAll[nCnt],
			&m_pMeshAll[nCnt]);

		D3DXMATERIAL *pMat = nullptr;

		//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
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

//���f���S���̔j������
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

//��������
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