#include "CBackground.h"
#include "CApplication.h"

//�萔�̒�`
#define TEX_COORD_BACKGROUND 0,1920,1080,0//�e�N�X�`���}�b�s���O
#define TEXTURE_BACKGROUND "Background.png"

//�G�̃R���X�g���N�^
CBackground::CBackground(float x, float y, float w, float h,CTexture* pt)
{
	Set(x, y, w, h);

	Texture(pt, TEX_COORD_BACKGROUND);
	//mpTexture->Load(TEXTURE_BACKGROUND);

	//Texture(GetTexture(), TEX_COORD_BACKGROUND);
}

void CBackground::Update()
{
}
