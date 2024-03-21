#pragma once
#include "CCharacter.h"

class CShadow :public CCharacter
{
public:
	//デフォルトコンストラクタ
	CShadow();
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	CShadow(float x, float y, float w, float h);

	//座標設定
	void SetShadow(float x, float y, float w, float h);

	//staticメソッドの宣言
	static CTexture* GetTexture();
	
private:
	CCharacter* mpParent;

	//static変数の宣言
	static CTexture mTexture;
};
