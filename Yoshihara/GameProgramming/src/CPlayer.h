#pragma once

#include "CCharacter.h"
#include "CInput.h"

class CPlayer : public CCharacter
{
public:

	//デフォルトコンストラクタ
	CPlayer();
	//コンストラクタ
	CPlayer(float x, float y, float w, float h);
	//デストラクタ
	~CPlayer();
	//更新処理
	void Update() override;

	//死亡処理
	void Death();

	//staticメソッドの宣言
	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//ジャンプ距離
	float mVx, mVy;

	//static変数の宣言
	static CTexture mTexture;
};