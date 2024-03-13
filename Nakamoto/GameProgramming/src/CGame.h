#pragma once
#include "CEnemy.h"
#include "CPlayer.h"
#include "CBackground.h"


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

private:
	void SetCamera();//カメラを設定
};
