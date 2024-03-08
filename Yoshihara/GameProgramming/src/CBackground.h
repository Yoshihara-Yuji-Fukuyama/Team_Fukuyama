#pragma once
#include "CCharacter.h"

class CBackground :public CCharacter
{
public:
	void Update();

	//背景のデフォルトコンストラクタ
	CBackground();

	/// <summary>
	/// 背景のコンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	CBackground(float x, float y, float w, float h);

	//staticメソッドの宣言
	static CTexture* GetTexture();

private:
	//static変数の宣言
	static CTexture mTexture;
};
