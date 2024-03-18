#include <stdio.h>
#include "CUiFont.h"

#define FONT "Font.png"         //フォントの画像
#define TIME_SIZE 800,1010,20,20//時間表示のサイズ
#define SCORE_SIZE 220,1010,20,20//スコア表示

#define TIME_MAX 189 //最大時間

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

	sprintf(str, "SCORE:%06d", mScore);
	mFont.Draw(SCORE_SIZE, str);
}
