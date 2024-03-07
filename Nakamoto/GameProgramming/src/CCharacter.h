#pragma once
#include "CTexture.h"
#include "CRectangle.h"
#include "CTask.h"

class CCharacter :public CRectangle, public CTask//�e�N���X��
{
public:
	//�L���t���O��Ԃ�
	bool GetEnabled();
	//�f�t�H���g�R���X�g���N�^
	CCharacter();
	//�f�X�g���N�^
	~CCharacter();
	//mpTexture��Ԃ�
	CTexture* GetTexture();

	/// <summary>
	/// �e�N�X�`���̐ݒ�
	/// </summary>
	/// <param name="pTexture">�e�N�X�`���̃|�C���^</param>
	/// <param name="left">�e�N�X�`���̍����W</param>
	/// <param name="right">�e�N�X�`���̉E���W</param>
	/// <param name="bottom">�e�N�X�`���̉����W</param>
	/// <param name="top">�e�N�X�`���̏���W</param>
	void Texture(CTexture* pTexture, int left, int right, int bottom, int top);

	virtual void Render();//�`��

	virtual void Update() = 0;//�`��

protected:
	bool mEnabled;//�L���t���O
private:
	CTexture* mpTexture;//�e�N�X�`��

	int mLeft, mRight, mBottom, mTop;//���A�E�A���A��

};

