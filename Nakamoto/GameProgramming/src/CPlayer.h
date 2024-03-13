#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"

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
	void Update();

	//staticメソッドの宣言
	static CPlayer* GetInstance();

	//staticメソッドの宣言
	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//ジャンプ距離
	bool isMove;        //移動しているか

	//コライダ
	CCollider mCollider;

	//static変数の宣言
	static CPlayer* mpInstance;//プレイヤーのインスタンス

	//static変数の宣言
	static CTexture mTexture;
};