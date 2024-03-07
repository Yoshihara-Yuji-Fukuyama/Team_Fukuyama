#include "CRectangle.h"
#include "CApplication.h"

//static変数の定義
CTexture CApplication::mTexture;

CTaskManager CApplication::mTaskManager;

//メソッドの定義
CTexture* CApplication::GetTexture()
{
	return &mTexture;
}

CTaskManager* CApplication::GetTaskManager()
{
	return &mTaskManager;
}

void CApplication::Start()
{
	mpGame = new CGame();
	mpGame->Start();
}



void CApplication::Update()
{
	mpGame->Update();
}