#pragma once
#include "CTexture.h"
#include "CEnemy.h"
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
	void Update();

	void Start();

	CGame();

	~CGame();

private:
	CEnemy* mpEnemy;

	CBackground* mpBackground;

};
