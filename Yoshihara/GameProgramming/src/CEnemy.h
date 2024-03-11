#pragma once
#include "CCharacter.h"
#include "CInput.h"

class CEnemy :public CCharacter
{
public:
	//更新処理
	void Update() override;

	//デフォルトコンストラクタ
	CEnemy();
	/// <summary>
	/// 敵のコンストラクタ
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	CEnemy(float x, float y, float w, float h);
	//デストラクタ
	~CEnemy();

	//死亡処理
	void Death();

	//staticメソッドの宣言
	static CTexture* GetTexture();

private:
	CInput mInput;
	//static変数の宣言
	static CTexture mTexture;

};