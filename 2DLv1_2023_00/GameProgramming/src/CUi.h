#pragma once
#include "CFont.h"

/*
CUi
ユーザーインターフェースクラス
*/

class CUi
{
public:
	CUi();
	
	void Time(int time); //Time(時間)

	void Hp(int hp); //HP

	void Enemy(int enemy);	//Enemy(敵の数)

	void Render();

	void Start(); //スタート画面

	void Over(); //ゲームオーバー表示

	void Clear(); //ゲームクリア表示

private:
	int mTime;  //経過時間

	int mHp; //HP

	int mEnemy; //敵の数

	CFont mFont;
};