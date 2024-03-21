#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"
#include "CCollisionManager.h"
#include "CBackground.h"

#define TEXTURE_TITLE "Title.png"            //タイトル画像
#define TEXTURE_TITLE_NAME "TitleName.png"   //タイトル名画像
#define TEXTURE_RESULT "Result.png"          //リザルト画像

#define TEXTURE_PLAYER "Player.png"          //プレイヤー画像

#define TEXTURE_SLIME "Slime.png"            //スライム画像
#define TEXTURE_ONI "Oni.png"                //鬼画像

#define TEXTURE_SKY "Sky.png"                //空画像
#define TEXTURE_CLOUD_A "CloudA.png"         //雲A画像
#define TEXTURE_CLOUD_B "CloudB.png"         //雲B画像
#define TEXTURE_CLOUD_C "CloudC.png"         //雲C画像
#define TEXTURE_BUILDING "Building.png"      //建物画像
#define TEXTURE_ROAD "Road.png"              //道画像

#define TEXTURE_HP_BAR "Hp.png"              //HP画像
#define TEXTURE_FRAME "Frame.png"            //枠画像

#define TEXTURE_SHADOW "Shadow.png"          //影の画像

#define TEXTURE_HEAL "Heal.png"              //回復の画像

#define TITLE_NAME_SET 960.0f,540.0f,359.0f,254.5f
#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h　背景1の初期位置
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h 背景2の初期位置
#define CHARACTER_SIZE 300.0f,300.0f                //w,h  キャラクターのサイズ
#define HP_SIZE_RED 235.0f, 12.0f                   //w,h  HpRedのサイズ
#define HP_SIZE_YELLOW 184.0f,12.0f                 //w,h HpYellowのサイズ
#define FACE_SIZE 50.0f,50.0f                     //w,h Faceのサイズ
#define FRAME_SIZE 60.0,60.0f                     //w,h Frameのサイズ

#define SLIME_HP 100 //スライムHP
#define ONI_HP 100 //鬼HP

#define ENEMY_MAX 4 //敵の最大数

CGame::CGame()
	:mScene(EGameScene::GameTitle)
	, isTitleCreate(false)
	, isEnter(false)
{		
	//テクスチャをロード
	//タイトル
	CTitle::GetTextureTitle()->Load(TEXTURE_TITLE);
	CTitle::GetTextureTitleName()->Load(TEXTURE_TITLE_NAME);
	//リザルト
	CTitle::GetTextureResult()->Load(TEXTURE_RESULT);
	//プレイヤー
	CPlayer::GetTexture()->Load(TEXTURE_PLAYER);
	//敵
	CEnemy::GetTextureSlime()->Load(TEXTURE_SLIME);
	CEnemy::GetTextureOni()->Load(TEXTURE_ONI);
	//背景
	CBackground::GetTextureSky()->Load(TEXTURE_SKY);
	CBackground::GetTextureCloudA()->Load(TEXTURE_CLOUD_A);
	CBackground::GetTextureCloudB()->Load(TEXTURE_CLOUD_B);
	CBackground::GetTextureCloudC()->Load(TEXTURE_CLOUD_C);
	CBackground::GetTextureBuilding()->Load(TEXTURE_BUILDING);
	CBackground::GetTextureRoad()->Load(TEXTURE_ROAD);
	//UI
	CUiTexture::GetTextureHpBar()->Load(TEXTURE_HP_BAR);
	CUiTexture::GetTextureFrame()->Load(TEXTURE_FRAME);
	CUiTexture::GetTextureFace()->Load(TEXTURE_PLAYER);
	//影
	CShadow::GetTexture()->Load(TEXTURE_SHADOW);
	//アイテム
	CHeal::GetTexture()->Load(TEXTURE_HEAL);
}



void CGame::Update()
{	
	switch (mScene)
	{
	case EGameScene::GameTitle://ゲームタイトル
		if (isTitleCreate == false)
		{
			new CTitle(TITLE_NAME_SET, CTitle::GetTextureTitleName());//タイトル名
			new CTitle(BACKGROUND_SET1, CTitle::GetTextureTitle());//タイトル
			
			isTitleCreate = true;//タイトルを生成している
		}
		CTaskManager::GetInstance()->Render();//タイトルを描画

		if (mInput.Key(VK_RETURN))
		{
			if (isEnter == false)
			{
				CTaskManager::GetInstance()->AllDelete();//タイトルを消す
				isTitleCreate = false;//タイトルを生成していない
				mScene = EGameScene::GameStart;//ゲームスタートへ変移
			}
			isEnter = true;
		}
		else
		{
			isEnter = false;
		}
		break;

	case EGameScene::GameStart://スタート
		//背景生成
		new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::Sky);
		new CBackground(BACKGROUND_SET2, nullptr, nullptr, (int)EFieldSort::Sky);
		new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::CloudA);
		new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::CloudB);
		new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::CloudC);
		new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::Building);
		new CBackground(BACKGROUND_SET1, nullptr, nullptr, (int)EFieldSort::Road);
		new CBackground(BACKGROUND_SET2, nullptr, nullptr, (int)EFieldSort::Road);

		//Ui生成
		new CUiTexture(FRAME_SIZE, CUiTexture::EUiType::Frame);
		new CUiTexture(FACE_SIZE, CUiTexture::EUiType::Face);
		new CUiTexture(HP_SIZE_YELLOW, CUiTexture::EUiType::HpYellow);
		new CUiTexture(HP_SIZE_RED, CUiTexture::EUiType::HpRed);

		//敵の数をゼロにする
		CEnemy::ZeroEnemyCount();
		mFrame = 0;//フレームカウンタをゼロに
		mCount = 1;//秒数カウンタを1に
		start = clock();//始まりの時間を保存

		mScene = EGameScene::Game;//ゲームへ変移

		break;

	case EGameScene::Game://ゲーム
		//時間が0になったら停止
		if (CUiFont::GetInstance()->GetTime() > 0)
		{
			clock_t end = clock();//経過時間
			double sec = (double)(end - start) / CLOCKS_PER_SEC;//秒数に変換
			if (sec >= mCount)
			{
				//1秒マイナス
				CUiFont::GetInstance()->SetTime();
				mCount++;
			}
			//敵生成
			CreateEnemy();
			//削除
			CTaskManager::GetInstance()->Delete();
			//更新
			CTaskManager::GetInstance()->Update();

		}
		//衝突判定
		CCollisionManager::GetInstance()->Collision();

		//カメラを設定
		SetCamera();

		//描画
		CTaskManager::GetInstance()->Render();

		//コライダの表示(確認用)
		//CCollisionManager::GetInstance()->Render();

		CCamera::End();

		//テキスト系UI描画
		CUiFont::GetInstance()->Render();

		if (CUiFont::GetInstance()->GetTime() <= 0 || CPlayer::GetInstance()->GetHp() <= 0)
		{
			mScene = EGameScene::GameResult;
		}

		break;

	case EGameScene::GameResult://リザルト
		//リザルト背景
		new CTitle(BACKGROUND_SET1, CTitle::GetTextureResult());
		//描画
		CTaskManager::GetInstance()->Render();
		//スコアの表示
		CUiFont::GetInstance()->EndRender();

		if (mInput.Key(VK_RETURN))
		{
			if (isEnter == false)
			{
				mScene = EGameScene::GameEnd;
			}
			isEnter = true;
		}
		else
		{
			isEnter = false;
		}
		break;

	case EGameScene::GameEnd://ゲーム終了
		CPlayer::DeleteInstance();
		CUiFont::DeleteInstance();
		CTaskManager::GetInstance()->AllDelete();
		mScene = EGameScene::GameTitle;
		break;

	}


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

	int posY;

	//frame/CREATE_TIMEのあまりがCREATE_TIMEの半分の数値の倍数なら生成
	//敵の数が最大値なら生成しない
	if (frame % CREATE_TIME % (CREATE_TIME / 2) == 0 && CEnemy::GetEnemyCount() < ENEMY_MAX)
	{

			//キャラタイプが偶数ならスライム
			if (charaType % 2 == 0)
			{
				posY = rand() % 125 + 125;//125から250未満の値がランダム
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, SLIME_HP, CEnemy::EEnemyType::Slime);
				//敵の数を１加算
				CEnemy::PlusEnemyCount();
			}
			//奇数なら鬼
			else
			{
				posY = rand() % 125 + 365;//365から490未満の値がランダム
				new CEnemy(CPlayer::GetInstance()->GetX() + 1000, posY, CHARACTER_SIZE, ONI_HP, CEnemy::EEnemyType::Oni);
				//敵の数を１加算
				CEnemy::PlusEnemyCount();
			}
	}
}
