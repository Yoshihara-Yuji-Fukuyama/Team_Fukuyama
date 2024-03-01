#pragma once
#include "CCharacter.h"

class CEnemy2 :public CCharacter
{
public:

	//衝突処理２
	void Collision();

	//衝突処理４
	void Collision(CCharacter* m, CCharacter* o);

	//CEnemy2(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CEnemy2(float x, float y, float w, float h, CTexture* pt);

	void Enemy0();

	//更新処理
	void Update();

	//敵の数を取得
	static int Num();


private:

	static int sNum; //敵の数

};