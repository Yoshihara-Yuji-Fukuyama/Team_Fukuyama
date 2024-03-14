#include "CFont.h"

//テクスチャをロード
void CFont::Load(const char* file, int row, int col)
{
	//テクスチャをロード
	mTexture.Load(file);
	//行と列を設定
	mTexture.SetRowCol(row, col);
}

//文字を描画
void CFont::Draw(float x, float y, float w, float h, char c)
{
	int i = c - 0x20;
	mTexture.DrawImage(x - w, x + w, y - h, y + h, i);
}

//文字列を描画
void CFont::Draw(float x, float y, float w, float h, char c[])
{
	//c[i]の中身が\0ではないなら続ける
	for (int i = 0; c[i] != '\0'; i++)
	{
		Draw(x, y, w, h, c[i]);
		x += w * 2;
	}
	return;
}