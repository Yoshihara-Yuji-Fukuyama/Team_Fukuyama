#include "CGame.h"
#include "CApplication.h"
#include "CBlock.h"
#include "CPlayer2.h"
#include "CEnemy2.h"
#include "CPoint.h"
#include "CCamera.h"
#include "main.h"


CGame::CGame()
	:mpUi(nullptr)
	, mTime(0)
{
	mpEnemy2->Enemy0(); //敵の数をゼロに設定

	mpUi = new CUi(); //UIクラスのインスタンスの生成

	//テクスチャの入力
	CApplication::Texture()->Load(TEXTURE);

	//定数の定義
	const int ROWS = 15; //行数

	const int COLS = 20; //列数

	//2次元配列のマップ
	int map[ROWS][COLS] =
	{
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,2,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
		{1,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,1},
		{0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
		{0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,4,0,0,3,0,0,4,0,1,0,0,0,0,0},
	};

	//マップの作成
	//行数分繰り返し
	for (int row = 0; row < ROWS; row++)
	{
		//列数分繰り返し
		for (int col = 0; col < COLS; col++)
		{

			//1の時、ブロック生成
			if (map[row][col] == 1)
			{
				//ブロックを生成して、キャラクタマネージャに追加
				CApplication::TaskManager()->Add(
					new CBlock(
						TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE,
						CApplication::Texture()));
			}


			//2の時、プレイヤー生成
			if (map[row][col] == 2)
			{
				//カメラ用差分
				mCdx =
					WINDOW_WIDTH / 4 - (TIPSIZE + TIPSIZE * 2 * col);

				mCdy =
					WINDOW_HEIGHT / 4 - (TIPSIZE + TIPSIZE * 2 * row);

				//プレイヤーを生成して、キャラクターマネージャに追加
				CApplication::TaskManager()->Add(
					//mpPlayerにプレイヤーのインスタンスのポインタを代入
					mpPlayer =
					new CPlayer2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE,
						CApplication::Texture()));
			}


			//3の時、敵生成
			if (map[row][col] == 3)
			{
				//敵を生成して、キャラクターマネージャに追加
				CApplication::TaskManager()->Add(
					new CEnemy2(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE,
						CApplication::Texture()));
			}



			//4の時、折り返しポイント生成
			if (map[row][col] == 4)
			{
				//折り返しポイントを生成して、キャラクタマネージャに追加
				CApplication::TaskManager()->Add(
					new CPoint(TIPSIZE + TIPSIZE * 2 * col,
						TIPSIZE + TIPSIZE * 2 * row,
						TIPSIZE, TIPSIZE,
						CCharacter::ETag::ETURN));
			}
		}
	}

}



void CGame::Update()
{
	//更新、衝突、削除、描画
	CApplication::TaskManager()->Update();

	CApplication::TaskManager()->Collision();
	
	CApplication::TaskManager()->Delete();

	CameraSet();

	CApplication::TaskManager()->Render();

	CCamera::End();


	//UI
	mpUi->Time(mTime++); //時間

	mpUi->Hp(CPlayer2::Hp()); //HP

	mpUi->Enemy(CEnemy2::Num()); //敵の数

	mpUi->Render();

}




void CGame::Start()
{
	//ゲームの描画
	CApplication::TaskManager()->Render();

	//UI処理
	mpUi->Hp(CPlayer2::Hp());

	mpUi->Enemy(CEnemy2::Num());

	mpUi->Render();

	mpUi->Start();

}




bool CGame::IsOver()
{
	//HPが0以下か判定結果を戻す
	return CPlayer2::Hp() <= 0;
}



void CGame::Over()
{

	CameraSet();

	//ゲームの描画
	CApplication::TaskManager()->Render();

	CCamera::End();

	//UI処理
	mpUi->Hp(CPlayer2::Hp());

	mpUi->Enemy(CEnemy2::Num());

	mpUi->Render();

	mpUi->Over();

	
}




bool CGame::IsClear()
{
	//敵の数が0以下か判定する
	return CEnemy2::Num() <= 0;
}



void CGame::Clear()
{
	CameraSet();

	//ゲームの描画
	CApplication::TaskManager()->Render();

	CCamera::End();

	//UI処理
	mpUi->Hp(CPlayer2::Hp());

	mpUi->Enemy(CEnemy2::Num());

	mpUi->Render();

	mpUi->Clear();

}




CGame::~CGame()
{
	//すべてのインスタンス削除
	CApplication::TaskManager()->AllDelete();

	//UIを生成しているとき
	if (mpUi != nullptr)
	{
		//UIを削除し、初期化
		delete mpUi;

		mpUi = nullptr;
	}
}



void CGame::CameraSet()
{
	float x = mpPlayer->X() + mCdx;

	float y = mpPlayer->Y() + mCdy;

	CCamera::Start(x - WINDOW_WIDTH / 4
		, x + WINDOW_WIDTH / 4
		, y - WINDOW_HEIGHT / 4
		, y + WINDOW_HEIGHT / 4);
}


