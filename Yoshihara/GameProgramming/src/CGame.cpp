#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"

#define PLAYER_STARTSET 100,300,300,300//x,y,w,h �v���C���[�̏����ʒu
#define ENEMY_STARTSET 1700,400,300,300//x,y,w,h�@�G�̏����ʒu
#define BACKGROUND_SET 960,540,960,540//x,y,w,h�@�w�i�̏����ʒu

CGame::CGame()
{		
	new CBackground(BACKGROUND_SET);	
	mpPlayer = new CPlayer(PLAYER_STARTSET);
	new CEnemy(ENEMY_STARTSET);

}



void CGame::Update()
{	
	CTaskManager::GetInstance()->Delete();
	CTaskManager::GetInstance()->Update();
	
	SetCamera();

	CTaskManager::GetInstance()->Render();

	CCamera::End();
}



void CGame::Start()
{

}



CGame::~CGame()
{
	CTaskManager::GetInstance()->AllDelete();
}

//�J������ݒ�
void CGame::SetCamera()
{
	float x = mpPlayer->GetX();

	CCamera::SetCamera(x - WINDOW_WIDTH / 2
		, x + WINDOW_WIDTH / 2
		, 0
		, WINDOW_HEIGHT);
}

