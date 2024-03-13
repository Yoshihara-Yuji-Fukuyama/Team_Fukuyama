#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"
#include "CCollisionManager.h"

#define TEXTURE_PLAYER "Player.png"          //プレイヤー画像
#define TEXTURE_BACKGROUND "Background.png"  //背景画像
#define TEXTURE_ENEMY "Slime.png"            //スライム画像

#define ENEMY_STARTSET 1700.0f,400.0f,300.0f,300.0f//x,y,w,h　敵の初期位置
#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h　背景1の初期位置
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h 背景2の初期位置

CGame::CGame()
{
	//テクスチャをロード
	CPlayer::GetTexture()->Load(TEXTURE_PLAYER);
	CEnemy::GetTexture()->Load(TEXTURE_ENEMY);
	CBackground::GetTexture()->Load(TEXTURE_BACKGROUND);

	//背景生成
	new CBackground(BACKGROUND_SET1, nullptr, nullptr);
	new CBackground(BACKGROUND_SET2, nullptr, nullptr);
	//プレイヤー生成
	CPlayer::GetInstance();
	//敵生成
	new CEnemy(ENEMY_STARTSET);

}



void CGame::Update()
{	
	//更新
	CTaskManager::GetInstance()->Update();

	CCollisionManager::GetInstance()->Collision();

	//カメラを設定
	SetCamera();

	//削除
	CTaskManager::GetInstance()->Delete();

	//描画
	CTaskManager::GetInstance()->Render();

	//コライダの表示(確認用)
	CCollisionManager::GetInstance()->Render();

	CCamera::End();
}



void CGame::Start()
{

}



CGame::~CGame()
{
	//すべて削除
	CTaskManager::GetInstance()->AllDelete();
}

//カメラを設定
void CGame::SetCamera()
{
	float x = CPlayer::GetInstance()->GetX();

	CCamera::SetCamera(x - (float)WINDOW_WIDTH / 2
		, x + (float)WINDOW_WIDTH / 2
		, 0
		, WINDOW_HEIGHT);
}
