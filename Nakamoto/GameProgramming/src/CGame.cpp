#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"

#define TEXTURE_BACKGROUND "Background.png"  //�w�i�摜
#define TEXTURE_ENEMY "Slime.png"            //�X���C���摜

#define PLAYER_STARTSET 100,300,300,300//x,y,w,h �v���C���[�̏����ʒu

#define ENEMY_STARTSET 1700.0f,400.0f,300.0f,300.0f//x,y,w,h�@�G�̏����ʒu

#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h�@�w�i1�̏����ʒu
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h �w�i2�̏����ʒu

CGame::CGame()
{
	CBackground::GetTexture()->Load(TEXTURE_BACKGROUND);
	CEnemy::GetTexture()->Load(TEXTURE_ENEMY);


	//�w�i����
	new CBackground(BACKGROUND_SET1, nullptr, nullptr);
	new CBackground(BACKGROUND_SET2, nullptr, nullptr);

	new CPlayer(PLAYER_STARTSET);
	new CEnemy(ENEMY_STARTSET);
}

void CGame::Update()
{
	CTaskManager::GetInstance()->Delete();
	CTaskManager::GetInstance()->Update();
	//�J������ݒ�
	SetCamera();

	CCollisionManager::GetInstance()->Collision();

	//�R���C�_�̕\��(�m�F�p)
	CCollisionManager::GetInstance()->Render();


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
	float x = CPlayer::GetInstance()->GetX();

	CCamera::SetCamera(x - WINDOW_WIDTH / 2
		, x + WINDOW_WIDTH / 2
		, 0
		, WINDOW_HEIGHT);
}
