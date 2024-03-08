#include "CGame.h"
#include "CApplication.h"

#define TEXTURE_ENEMY "Slime.png"
#define TEXTURE_BACKGROUND "Background.png"
#define ENEMY_STARTSET 1700,300,300,300//x,y,w,h
#define BACKGROUND_SET 960,540,960,540//x,y,w,h

CGame::CGame()
{	
	new CBackground(BACKGROUND_SET);
	new CEnemy(ENEMY_STARTSET);
}



void CGame::Update()
{	
	CTaskManager::GetInstance()->Delete();
	CTaskManager::GetInstance()->Update();
	CTaskManager::GetInstance()->Render();
}



void CGame::Start()
{

}



CGame::~CGame()
{
	CTaskManager::GetInstance()->AllDelete();
}


