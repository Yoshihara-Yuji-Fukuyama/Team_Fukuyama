#include "CApplication.h"

void CApplication::Start()
{
	mpPlayer = new CPlayer();
	mTexture.Load(ENEMY_TEXTURE);
	mpPlayer->Set(100.0f, 150.0f, 100.0f, 50.0f);

	mpPlayer->Texture(&mTexture, 400, 0, 1080, 815);
	
}


void CApplication::Update()
{
	mpPlayer->Render();
	mpPlayer->Update();
}

