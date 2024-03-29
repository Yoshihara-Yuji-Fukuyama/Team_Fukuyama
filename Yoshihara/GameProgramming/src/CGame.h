#pragma once
#include "CEnemy.h"
#include "CBackground.h"
#include "CPlayer.h"
#include "CUiFont.h"
#include "CUiTexture.h"
#include "CUiPowerUp.h"
#include "CShadow.h"
#include "CInput.h"
#include "CTitle.h"
#include "CHeal.h"
#include <time.h>

/*
CGameクラス
ゲームクラス
ゲームのマップを作成し、
キャラクタを配置する
*/

class CGame
{
public:
	enum class EGameScene
	{
		GameTitle,
		GameStart,
		Game,
		PowerUp,
		GameResult,
		GameEnd,
	};
	//更新
	void Update();
	//初期処理
	void Start();

	//デフォルトコンストラクタ
	CGame();
	//デストラクタ
	~CGame();

	//敵生成
	void CreateEnemy();

private:
	CInput mInput;

	int mPop;

	void SetCamera();//カメラを設定

	clock_t start;//ゲーム始まりの時間を保存
	clock_t pouse;//ゲーム中断の始まりの時間を保存

	int mFrame;//フレームカウンタ

	double mCount;//秒数カウンタ

	bool isTitleCreate;//タイトルを生成しているか

	bool isStartTime;//始まりの時間を保存しているか

	bool isEnter;//エンターを押して離すまでをセットに

	bool isPowerUpGet;//強化を獲得したか

	int mPowerUpX;//強化の回数

	EGameScene mScene;//ゲームのシーン
};
