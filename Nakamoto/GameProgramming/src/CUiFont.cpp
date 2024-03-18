#include <stdio.h>
#include "CUiFont.h"

#define FONT "Font.png"         //フォントの画像
#define TIME_SIZE 1000,1000,20,20//時間表示のサイズ
#define SCORE_SIZE 520,1000,20,20//スコア表示


//デフォルトコンストラクタ
CUiFont::CUiFont()
	:mTime(0)
	, mScore(0)
{
	mFont.Load(FONT, 1, 64);
}

void CUiFont::SetTime(int time)
{
	mTime = time;
}

void CUiFont::SetScore(int score)
{
	mScore = score;
}

void CUiFont::Render()
{
	char str[16];

	//時間
	sprintf(str, "TIME:%03d", mTime);
	mFont.Draw(TIME_SIZE, str);

	sprintf(str, "SCORE:%04d", mScore);
	mFont.Draw(SCORE_SIZE, str);
}
