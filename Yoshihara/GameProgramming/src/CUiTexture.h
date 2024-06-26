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
		Item,
	};
	//デフォルトコンストラクタ
	CUiTexture();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	/// <param name="uiType">UIの種類</param>
	/// <param name="left">テクスチャの左</param>
	/// <param name="right">テクスチャの右</param>
	/// <param name="bottom">テクスチャの下</param>
	/// <param name="top">テクスチャの上</param>
	CUiTexture(float w, float h, EUiType uiType, int left = 0, int right = 0, int bottom = 0, int top = 0);

	//更新
	void Update();

	//staticメソッドの宣言
	static CTexture* GetTextureHpBar();

	static CTexture* GetTextureFrame();

	static CTexture* GetTextureFace();

	static void SetItemNum();
private:
	//UIの種類
	EUiType mUiType;
	//現在のHP
	float mHp;
	//HPの最大値
	float mMaxHp;
	//幅の保存
	float mW;
	//アイテム数保存
	int mItemNumSave;

	//static変数の宣言
	static CTexture mTextureHpBar;

	static CTexture mTextureFrame;

	static CTexture mTextureFace;

	static int mItemNum;
};