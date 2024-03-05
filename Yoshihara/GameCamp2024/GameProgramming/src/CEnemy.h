#pragma once
#include "CCharacter.h"

//定数の定義
#define TEXTURE "ge-mu.png"

class CEnemy :public CCharacter
{
public:
	void Update();

	/// <summary>
	/// 敵のコンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="pt">テクスチャのポインタ</param>
	CEnemy(float x, float y, float w, float h, CTexture* pt);

private:


	CEnemy(float x, float y, float w, float h, CTexture* pt);

};