#include "CApplication.h"
#include "CRectangle.h"

void CApplication::Start()
{
	mRectangle.Set(400.0f, 300.0f, 200.0f, 100.0f);
	mTexture.Load("ge-mu.png");
}

void CApplication::Update()
{
	mRectangle.Render();
	mTexture.DrawImage(0.0f, 0.0f, 1080.0f, 1920.0f, 0.0f, 0.0f, 100.0, 100.0f);
}
