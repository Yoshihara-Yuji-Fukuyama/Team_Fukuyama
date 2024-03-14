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
		Face,
	};
	//デフォルトコンストラクタ
	CUiTexture();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="uiType">UIの種類</param>
	CUiTexture(float w, float h, EUiType uiType);

	//更新
	void Update();

	//staticメソッドの宣言
	static CTexture* GetTextureHpBar();

	static CTexture* GetTextureFrame();

	static CTexture* GetTextureFace();
private:
	//UIの種類
	EUiType mUiType;
	//現在のHP
	float mHp;
	//HPの最大値
	float mMaxHp;
	//幅の保存
	float mW;

	//static変数の宣言
	static CTexture mTextureHpBar;

	static CTexture mTextureFrame;

	static CTexture mTextureFace;
};