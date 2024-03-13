#pragma once

#include "CCharacter.h"
#include "CInput.h"
#include "CCollider.h"
#include "CAnimation.h"

class CPlayer : public CCharacter, public CAnimation
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

	//移動入力
	void Move();

	//死亡処理
	void Death();

	//アニメーションを設定
	void SetAnimation();
	//ジャンプアニメーション
	void JumpAnimation();

	//staticメソッドの宣言
	static CPlayer* GetInstance();

	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//ジャンプ距離

	//コライダ
	CCollider mCollider;

	//static変数の宣言
	static CPlayer* mpInstance;//プレイヤーのインスタンス

	static CTexture mTexture;
};