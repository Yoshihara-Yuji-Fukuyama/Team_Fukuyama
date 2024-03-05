#include "CApplication.h"

void CApplication::Start()
{
	mRectangle.Set(400.0f, 300.0f, 200.0f, 100.0f);
	mTexture.Load("ge-mu.pig");
}


void CApplication::Update()
{
	//mRectangle.Render();
	mTexture.DrawImage(mRectangle.GetX() - mRectangle.GetW(),
		mRectangle.GetX() + mRectangle.GetW(),
		mRectangle.GetY() - mRectangle.GetH(),
		mRectangle.GetY() + mRectangle.GetH(),
		0, 570, 1010, 430
	);
}

