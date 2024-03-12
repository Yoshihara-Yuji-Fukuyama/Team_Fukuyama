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

	//移動入力
	void Move();

	//死亡処理
	void Death();

	//移動アニメーション
	void MoveAnimation();

	//staticメソッドの宣言
	static CPlayer* GetInstance();

	static CTexture* GetTexture();

private:
	CInput mInput;
	float mJump;		//ジャンプ距離
	bool isMove;        //移動しているか

	//static変数の宣言
	static CPlayer* mpInstance;//プレイヤーのインスタンス

	static CTexture mTexture;
};