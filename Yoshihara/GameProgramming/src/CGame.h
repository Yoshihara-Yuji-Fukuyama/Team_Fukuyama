#pragma once
#include "CEnemy.h"
#include "CBackground.h"
#include "CPlayer.h"

/*
CGameクラス
ゲームクラス
ゲームのマップを作成し、
キャラクタを配置する
*/

class CGame
{
public:
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
	void SetCamera();//カメラを設定

	int mFrame;//フレームカウンタ
};
