#pragma once
#include "CCharacter.h"

class CBullet :public CCharacter
{
public:
	void Update();

	bool Collision(CRectangle* rect);

	CBullet();

	CBullet(float x, float y, float w, float h,
		float l, float r, float b, float t, CTexture* pt);
	/*CBullet(X座標, Y座標, 幅, 高さ,
        画像左,画像右,画像下,画像上,テクスチャのポインタ)*/

	//衝突処理2
	void Collision();

	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
};