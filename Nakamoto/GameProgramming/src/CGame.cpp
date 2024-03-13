#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"

#define TEXTURE_BACKGROUND "Background.png"  //背景画像
#define TEXTURE_ENEMY "Slime.png"            //スライム画像

#define PLAYER_STARTSET 100,300,300,300//x,y,w,h プレイヤーの初期位置

#define ENEMY_STARTSET 1700.0f,400.0f,300.0f,300.0f//x,y,w,h　敵の初期位置

#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h　背景1の初期位置
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h 背景2の初期位置

CGame::CGame()
{
	CBackground::GetTexture()->Load(TEXTURE_BACKGROUND);
	CEnemy::GetTexture()->Load(TEXTURE_ENEMY);


	//背景生成
	new CBackground(BACKGROUND_SET1, nullptr, nullptr);
	new CBackground(BACKGROUND_SET2, nullptr, nullptr);

	new CPlayer(PLAYER_STARTSET);
	new CEnemy(ENEMY_STARTSET);
}

void CGame::Update()
{
	CTaskManager::GetInstance()->Delete();
	CTaskManager::GetInstance()->Update();
	//カメラを設定
	SetCamera();

	CCollisionManager::GetInstance()->Collision();

	//コライダの表示(確認用)
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

//カメラを設定
void CGame::SetCamera()
{
	float x = CPlayer::GetInstance()->GetX();

	CCamera::SetCamera(x - WINDOW_WIDTH / 2
		, x + WINDOW_WIDTH / 2
		, 0
		, WINDOW_HEIGHT);
}
