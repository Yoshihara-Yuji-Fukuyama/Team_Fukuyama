#include "CApplication.h"

#define PLAYER_TEXTURE "�S�Q�Z�b�g.png"
#define ONI_TEXCOORD 600 ,0 ,1200 ,600	//�S�ҋ@�P

void CApplication::Start()
{
	mTexture.Load(PLAYER_TEXTURE);
	mpPlayer = new CPlayer();
	mpPlayer->Set(100.0f, 300.0f, 300.0f, 300.0f);
	mpPlayer->Texture(&mTexture, ONI_TEXCOORD);
}


void CApplication::Update()
{
	mpPlayer->Render();
	mpPlayer->Update();
}

