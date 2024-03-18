#pragma once
#include "CFont.h"

class CUiFont
{
public:
	//デフォルトコンストラクタ
	CUiFont();

	//時間
	void SetTime();

	//時間の取得
	int GetTime();

	//スコア
	void SetScore(int score);

	//文字の描画
	void Render();

	//staticメソッドの宣言
	static CUiFont* GetInstance();

private:
	int mTime;//タイムリミット

	int mScore;//得点

	CFont mFont;

	//static変数の宣言
	static CUiFont* mpInstance;

};