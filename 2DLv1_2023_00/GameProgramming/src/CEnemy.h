#pragma once
#include "CCharacter.h"

class CEnemy :public CCharacter
{
public:
	void Update();

	bool Collision(CRectangle* rect);

	CEnemy(float x, float y, float w, float h,
		float l, float r, float b, float t, CTexture* pt);
	/*CEnemy(X座標, Y座標, 幅, 高さ,
	画像左,画像右,画像下,画像上,テクスチャのポインタ)*/

	void Collision();

	void Collision(CCharacter* m, CCharacter* o);
};