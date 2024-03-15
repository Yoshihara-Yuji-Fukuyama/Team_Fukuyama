#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"

#include "CCollisionManager.h"

#define TEXTURE_PLAYER "Player.png"          //プレイヤー画像
#define TEXTURE_BACKGROUND "Background.png"  //背景画像
#define TEXTURE_SLIME "Slime.png"            //スライム画像
#define TEXTURE_ONI "Oni.png"                //鬼画像

#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h　背景1の初期位置
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h 背景2の初期位置
#define CHARACTER_SIZE 300.0f,300.0f                //w,h  キャラクターのサイズ

CGame::CGame()
	:mFrame(0)
{
	//テクスチャをロード
	CPlayer::GetTexture()->Load(TEXTURE_PLAYER);
	CEnemy::GetTextureSlime()->Load(TEXTURE_SLIME);
	CEnemy::GetTextureOni()->Load(TEXTURE_ONI);
	CBackground::GetTexture()->Load(TEXTURE_BACKGROUND);

	//背景生成
	new CBackground(BACKGROUND_SET1, nullptr, nullptr);
	new CBackground(BACKGROUND_SET2, nullptr, nullptr);
	//プレイヤー生成
	CPlayer::GetInstance();
	new CEnemy(CPlayer::GetInstance()->GetX() + 1000, 300, CHARACTER_SIZE, CEnemy::EEnemyType::Slime);
}

void CGame::Update()
{	
	//敵生成
	//CreateEnemy();

	//更新
	CTaskManager::GetInstance()->Update();

	//衝突判定
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

//エネミー生成
void CGame::CreateEnemy()
{
	const int CREATE_TIME = 500;//生成間隔計算用
	int frame = mFrame++;//フレーム計算

	int charaType = rand();//偶数か奇数がランダム

	int posX = rand();//偶数か奇数がランダム
	int posY = rand() % 250;//250未満の値がランダム

	//frame/CREATE_TIMEのあまりがCREATE_TIMEの半分の数値の倍数なら生成
	if (frame % CREATE_TIME % (CREATE_TIME / 2) == 0)
	{
		//偶数なら前方に生成
		if (posX % 2 == 0)
		{
			//キャラタイプが偶数ならスライム
			if (charaType % 2 == 0)
			{
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, CEnemy::EEnemyType::Slime);
			}
			//奇数なら鬼
			else
			{
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, CEnemy::EEnemyType::Oni);
			}
		}
		//奇数なら後方に生成
		else
		{
			//キャラタイプが偶数ならスライム
			if (charaType % 2 == 0)
			{
				new CEnemy(CPlayer::GetInstance()->GetX() - 1000, posY, CHARACTER_SIZE, CEnemy::EEnemyType::Slime);
			}
			//奇数なら鬼
			else
			{
				new CEnemy(CPlayer::GetInstance()->GetX() - 1000, posY, CHARACTER_SIZE, CEnemy::EEnemyType::Oni);
			}
		}

	}
}
