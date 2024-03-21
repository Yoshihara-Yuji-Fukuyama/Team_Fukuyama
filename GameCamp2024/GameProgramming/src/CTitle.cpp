#include "CTitle.h"
//�e�N�X�`���}�b�s���O
#define TEX_TITLE 0,1920,1080,0 
#define TEX_TITLE_NAME 0,718,509,0
#define TEX_RESULT 0,1920,1080,0

//static�ϐ��̐錾
CTexture CTitle::mTextureTitle;
CTexture CTitle::mTextureTitleName;
CTexture CTitle::mTextureResult;


CTexture* CTitle::GetTextureTitle()
{
	return &mTextureTitle;
}
CTexture* CTitle::GetTextureTitleName()
{
	return &mTextureTitleName;
}
CTexture* CTitle::GetTextureResult()
{
	return &mTextureResult;
}

//�f�t�H���g�R���X�g���N�^
CTitle::CTitle()
	:CCharacter((int)CTaskPriority::Title)
{

}
//�R���X�g���N�^
CTitle::CTitle(float x, float y, float w, float h, CTexture* texture)
	:CTitle()
{
	Set(x, y, w, h);

	//�e�N�X�`�����^�C�g���Ȃ�
	if (texture == GetTextureTitle())
	{
		Texture(texture, TEX_TITLE);
	}
	else if (texture == GetTextureTitleName())
	{
		Texture(texture, TEX_TITLE_NAME);
	}
	else
	{
		Texture(texture, TEX_RESULT);
	}
	
}