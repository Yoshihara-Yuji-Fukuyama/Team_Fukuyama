#pragma once
#include "CCharacter.h"
#include "CTexture.h"

class CTitle :public CCharacter
{
public:
	//�f�t�H���g�R���X�g���N�^
	CTitle();
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	/// <param name="texture">�e�N�X�`���̃|�C���^</param>
	CTitle(float x, float y, float w, float h, CTexture* texture);
	//static���\�b�h�̐錾
	static CTexture* GetTextureTitle();
	static CTexture* GetTextureTitleName();
	static CTexture* GetTextureResult();

private:
	//static�ϐ��̐錾
	static CTexture mTextureTitle;
	static CTexture mTextureTitleName;
	static CTexture mTextureResult;
};