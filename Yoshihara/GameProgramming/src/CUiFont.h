#pragma once
#include "CFont.h"

class CUiFont
{
public:
	//デフォルトコンストラクタ
	CUiFont();

	//残り時間
	void SetTime(int time);

	//スコア
	void SetScore(int score);

	//文字の描画
	void Render();


private:
	int mTime;//タイムリミット

	int mScore;//得点

	CFont mFont;


};