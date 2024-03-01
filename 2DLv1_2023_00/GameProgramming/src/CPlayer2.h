#pragma once
#include "CCharacter.h"
#include "CInput.h"
#include "CSound.h"

class CPlayer2 :public CCharacter
{
public:
	//CPlayer2(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CPlayer2(float x, float y, float w, float h, CTexture* pt);

	//更新処理
	void Update();

	//衝突処理２
	void Collision();

	//衝突処理４
	void Collision(CCharacter* m, CCharacter* o);

	//HPを取得
	static int Hp();

private:
	CInput mInput;

	static int sHp; //HP

	int mInvincible; //無敵カウンタ

	CSound mSoundJump; //ジャンプSE
};