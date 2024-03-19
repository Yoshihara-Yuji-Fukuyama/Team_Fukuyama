#pragma once
#include "CCharacter.h"
#include "CTexture.h"

class CTitle :public CCharacter
{
public:
	//デフォルトコンストラクタ
	CTitle();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="texture">テクスチャのポインタ</param>
	CTitle(float x, float y, float w, float h, CTexture* texture);
	//staticメソッドの宣言
	static CTexture* GetTextureTitle();
	static CTexture* GetTextureTitleName();
	static CTexture* GetTextureResult();

private:
	//static変数の宣言
	static CTexture mTextureTitle;
	static CTexture mTextureTitleName;
	static CTexture mTextureResult;
};