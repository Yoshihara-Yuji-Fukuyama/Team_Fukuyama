#pragma once
#include "CUi.h"
#include "CEnemy2.h"
#include"CPlayer2.h"

//定数の定義
#define TEXTURE "image.png" //テクスチャのファイル名
#define TIPSIZE 20.0f //マップ要素のサイズ

/*
CGameクラス
ゲームクラス
ゲームのマップを作成し、
キャラクタを配置する
*/

class CGame
{
public:
	CGame(); //デフォルトコンストラクタ(初期処理)

	void Update(); //更新処理

	void Start(); //スタート処理

	//ゲームオーバー判定
	//true:ゲームオーバー
	bool IsOver();

	//ゲームオーバー処理
	void Over();

	//ゲームクリア判定
	//true:ゲームクリア
	bool IsClear();

	//ゲームクリア処理
	void Clear();

	//デストラクタ
	~CGame();

private:
	CUi* mpUi; //UIクラスのポインタ

	CEnemy2* mpEnemy2;

	int mTime; //経過時間

	int mCdx, mCdy; //カメラとプレイヤーの座標の差分

	CPlayer2* mpPlayer; //プレイヤーのポインタ

	void CameraSet(); //カメラ設定

};
