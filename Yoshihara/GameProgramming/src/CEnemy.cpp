#include "CEnemy.h"
#include "CApplication.h"

//�萔�̒�`
#define TEX_COORD_ENEMY 450,860,392,121//�e�N�X�`���}�b�s���O
#define TEXTURE_ENEMY "Slime.png"


//�G�̃R���X�g���N�^
CEnemy::CEnemy(float x, float y, float w, float h,CTexture* pt)
{
	Set(x, y, w, h);

	Texture(pt, TEX_COORD_ENEMY);

	//mpTexture->Load(TEXTURE_ENEMY);

	//Texture(GetTexture(), TEX_COORD_ENEMY);
}

void CEnemy::Update()
{

}


