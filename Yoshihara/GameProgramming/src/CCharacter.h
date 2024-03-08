#pragma once
#include "CTexture.h"
#include "CRectangle.h"
#include "CTask.h"

class CCharacter :public CRectangle,public CTask//�e�N���X��
{
public:
	//�f�t�H���g�R���X�g���N�^
	CCharacter();
	/// <summary>
	/// �w�i�̃R���X�g���N�^
	/// </summary>
	/// <param name="priority">�D��x</param>
	CCharacter(int priority);
	//�f�X�g���N�^
	~CCharacter();
	//mpTexture��Ԃ�
	CTexture* GetTexture();
	//�L���t���O��Ԃ�
	bool GetEnabled();

	/// <summary>
	/// �e�N�X�`���̐ݒ�
	/// </summary>
	/// <param name="pTexture">�e�N�X�`���̃|�C���^</param>
	/// <param name="left">�e�N�X�`���̍����W</param>
	/// <param name="right">�e�N�X�`���̉E���W</param>
	/// <param name="bottom">�e�N�X�`���̉����W</param>
	/// <param name="top">�e�N�X�`���̏���W</param>
	void Texture(CTexture* pTexture,int left, int right, int bottom, int top);

	void Render();//�`��

protected:
	bool mEnabled;//�L���t���O

private:
	CTexture* mpTexture;//�e�N�X�`��

	int mLeft, mRight, mBottom, mTop;//���A�E�A���A��

};

