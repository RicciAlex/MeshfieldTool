//=============================================================================
//
// Letter.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef LETTER_H
#define LETTER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CLetter : public CObject_2D
{
public:
	CLetter();																//�R���X�g���N�^
	CLetter(const int nPriority);											//�R���X�g���N�^
	~CLetter() override;													//�f�X�g���N�^

	HRESULT Init(void) override;											//����������
	void Uninit(void) override;												//�I������
	void Update(void) override;												//�X�V����
	void Draw(void) override;												//�I������

	bool ConvertInNumber(const int nNum);
	bool ConvertInSymbol(const char symbol);						

	void SetPrevLetter(CLetter* pPrev);
	void SetNextLetter(CLetter* pNext);

	CLetter* GetPrevLetter(void);
	CLetter* GetNextLetter(void);

	static CLetter* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter);			//��������
	static CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum);
	static CLetter* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter, const int nPriority);			//��������
	static CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum, const int nPriority);

private:

	CLetter* m_pPreviousLetter;
	CLetter* m_pNextLetter;
};

#endif
