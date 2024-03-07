#pragma once
#include "CCharacter.h"

class CBackground :public CCharacter
{
public:
	void Update();

	/// <summary>
	/// 背景のコンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="pt">テクスチャのポインタ</param>
	CBackground(float x, float y, float w, float h,CTexture* pt);

private:

};
