#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CTask.h"

#define VELOCITY 2.0f   //移動速度

class CCharacter :public CRectangle,public CTask//親クラス名
{

public:

	bool Enabled();

	//衝突処理2
	virtual void Collision() {};

	//衝突処理4
	//Collision(自分のポインタ,衝突相手のポインタ)
	virtual void Collision(CCharacter* m, CCharacter* o) {};

	enum class ETag  //識別子
	{
		EZERO,       //初期値
		EBULLET,     //弾
		EENEMY,      //的
		EPLAYER,     //プレイヤー
		ETURN,       //折り返し
		EBLOCK,      //ブロック
	};

	enum class EState //状態
	{
		EMOVE,  //移動
		ESTOP,  //停止
		EJUMP,  //ジャンプ
		ECRY,  //泣く
	};
	//デフォルトコンストラクタ
	CCharacter();
	//デストラクタ
	~CCharacter();

	CTexture* Texture();

	void Texture(CTexture* pTexture,
		int left, int rihgt, int bottom, int top);

	virtual void Render();

	virtual void Update() = 0;

	void Move();

	ETag Tag();

	EState State(); //状態を取得する

protected:

	EState mState;

	ETag mTag;   //識別子

	bool mEnabled;//有効フラグ

	float mVy; //Y軸速度

	float mVx; //X軸速度

private:
	CTexture* mpTexture;

	int mLeft, mRight, mBottom, mTop;

};