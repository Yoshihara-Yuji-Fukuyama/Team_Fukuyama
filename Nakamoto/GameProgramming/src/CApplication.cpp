#include "CApplication.h"

void CApplication::Start()
{
	mTexture.Load(ENEMY_TEXTURE);
	mPlayer.Set(100.0f, 150.0f, 100.0f, 50.0f);

	mPlayer.Texture(&mTexture, 400, 0, 1080, 815);
	
}


void CApplication::Update()
{
	mPlayer.Render();
	mPlayer.Update();
}

