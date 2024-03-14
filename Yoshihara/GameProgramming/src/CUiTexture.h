#pragma once
#include "CCharacter.h"

class CUiTexture :public CCharacter
{
public:
	//UIの種類
	enum class EUiType
	{
		HpRed,
		HpYellow,
		Frame,
		Player,
	};
	//デフォルトコンストラクタ
	CUiTexture();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="uiType">UIの種類</param>
	CUiTexture(float x, float y, float w, float h, EUiType uiType);

	//staticメソッドの宣言
	static CTexture* GetTextureHpBar();

	static CTexture* GetTextureFrame();

	static CTexture* GetTextureFace();
private:
	//UIの種類
	EUiType mUiType;

	//static変数の宣言
	static CTexture mTextureHpBar;

	static CTexture mTextureFrame;

	static CTexture mTextureFace;
};