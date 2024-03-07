#include "CRectangle.h"
#include "CApplication.h"

//static�ϐ��̒�`
CTexture CApplication::mTexture;

CTaskManager CApplication::mTaskManager;

//���\�b�h�̒�`
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