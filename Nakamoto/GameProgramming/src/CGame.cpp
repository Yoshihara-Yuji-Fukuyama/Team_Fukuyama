#include "CGame.h"
#include "CApplication.h"

#define PLAYER_STARTSET 100,300,300,300//x,y,w,h �v���C���[�̏����ʒu
#define ENEMY_STARTSET 1700,300,300,300//x,y,w,h�@�G�̏����ʒu
#define BACKGROUND_SET 960,540,960,540//x,y,w,h�@�w�i�̏����ʒu

CGame::CGame()
{
	new CBackground(BACKGROUND_SET);
	new CPlayer(PLAYER_STARTSET);
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