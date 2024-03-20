#include <stdio.h>
#include "CUiFont.h"

#define FONT "Font.png"         //フォントの画像
#define TIME_SIZE 800,1010,20,20//時間表示のサイズ
#define SCORE_SIZE 220,1010,20,20//スコアサイズ
#define SCORE_SIZE_END1 560,700,100,100 //終了後のスコアのサイズ
#define SCORE_SIZE_END2 710,400,50,50   //終了後のスコアの数値のサイズ

#define TIME_MAX 180 //最大時間

//static変数の宣言
CUiFont* CUiFont::mpInstance;

//staticメソッドの宣言
CUiFont* CUiFont::GetInstance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CUiFont();
	}
	return mpInstance;
}

void CUiFont::DeleteInstance()
{
	if (mpInstance != nullptr)
	{
		delete mpInstance;
		mpInstance = nullptr;
	}
}

//デフォルトコンストラクタ
CUiFont::CUiFont()
	:mTime(TIME_MAX)
	, mScore(0)
{
	mFont.Load(FONT, 1, 64);
}

void CUiFont::SetTime()
{
	mTime = mTime--;
}

int CUiFont::GetTime()
{
	return mTime;
}

void CUiFont::SetScore(int score)
{
	mScore = mScore + score;
}

void CUiFont::Render()
{
	char str[16];

	//時間
	sprintf(str, "TIME:%03d", mTime);
	mFont.Draw(TIME_SIZE, str);
	//スコア
	sprintf(str, "SCORE:%06d", mScore);
	mFont.Draw(SCORE_SIZE, str);
}

void CUiFont::EndRender()
{
	char str[16];

	//スコア
	sprintf(str, "SCORE");
	mFont.Draw(SCORE_SIZE_END1, str);

	//スコア数値
	sprintf(str, "%06d", mScore);
	mFont.Draw(SCORE_SIZE_END2, str);
}
