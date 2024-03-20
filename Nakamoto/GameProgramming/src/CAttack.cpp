#include "CAttack.h"
#include "CCollisionManager.h"

//確認用 削除予定
#include <stdio.h>

#define LIFE 50

#define ATTACK_X_POINT1 130	//攻撃1コライダの生成位置のX座標の加算値
#define ATTACK_X_POINT2 120	//攻撃2コライダの生成位置のX座標の加算値
#define ATTACK_X_POINT3 200	//攻撃3コライダの生成位置のX座標の加算値

#define ATTACK_Y_POINT1 80	//1段目の攻撃コライダの生成位置のY座標の加算値
#define ATTACK_Y_POINT2 40  //2段目の攻撃コライダの生成位置のY座標の加算値

#define ATTACK_WIDTH1 130	//1段目の幅
#define ATTACK_WIDTH2 120	//2段目の幅
#define ATTACK_WIDTH3 70	//3段目の幅

#define ATTACK_HEIGHT1 100	//1段目の高さ
#define ATTACK_HEIGHT2 170	//2段目の高さ
#define ATTACK_HEIGHT3 200	//3段目の高さ

#define ATTACK_X_POINT_S 110	//スライムの攻撃の生成位置のX座標の加算値
#define ATTACK_Y_POINT_S 0	//スライムの攻撃の生成位置のY座標の加算値
#define ATTACK_WIDTH_S 60	//スライムの攻撃の幅
#define ATTACK_HEIGHT_S 80	//スライムの攻撃の高さ

#define ATTACK_X_POINT_O 100	//鬼の攻撃の生成位置のX座標の加算値
#define ATTACK_WIDTH_O 50		//鬼の攻撃の幅
#define ATTACK_HEIGHT_O 200		//鬼の攻撃の高さ


CAttack::CAttack(CCharacter* parent, float* x, float* y, float* z, float mvx, int attackNumber)
	:CCharacter()
	,mLife(LIFE)
{
	mZ = *z;
	mVx = mvx;
	
	if (mVx < 0) 
	{
		//左向き
		//プレイヤーの1段目の攻撃
		if (attackNumber == 1)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH1, ATTACK_HEIGHT1, CCollider::EColliderType::EPATTACK1);
			mX = *x - ATTACK_X_POINT1;
			mY = *y + ATTACK_Y_POINT1;
			printf("左攻撃1\n");
		}
		//プレイヤーの2段目の攻撃
		else if (attackNumber == 2)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH2, ATTACK_HEIGHT2, CCollider::EColliderType::EPATTACK2);
			mX = *x - ATTACK_X_POINT2;
			mY = *y + ATTACK_Y_POINT2;
			printf("左攻撃2\n");
		}
		//プレイヤーの3段目の攻撃
		else if (attackNumber == 3)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH3, ATTACK_HEIGHT3, CCollider::EColliderType::EPATTACK3);
			mX = *x - ATTACK_X_POINT3;
			mY = *y;
			printf("左攻撃3\n");
		}
		//スライムの攻撃
		else if (attackNumber == 4)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH_S, ATTACK_HEIGHT_S, CCollider::EColliderType::ESATTACK);
			mX = *x - ATTACK_X_POINT_S;
			mY = *y + ATTACK_Y_POINT_S;
		}
		//鬼の攻撃
		else if (attackNumber == 5)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH_O, ATTACK_HEIGHT_O, CCollider::EColliderType::EOATTACK);
			mX = *x - ATTACK_X_POINT_O;
			mY = *y;
		}
	}
	else
	{
		//右向き
		//プレイヤーの1段目の攻撃
		if (attackNumber == 1)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH1, ATTACK_HEIGHT1, CCollider::EColliderType::EPATTACK1);
			mX = *x + ATTACK_X_POINT1;
			mY = *y + ATTACK_Y_POINT1;
			printf("右攻撃1\n");
		}
		//プレイヤーの2段目の攻撃
		else if (attackNumber == 2)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH2, ATTACK_HEIGHT2, CCollider::EColliderType::EPATTACK2);
			mX = *x + ATTACK_X_POINT2;
			mY = *y + ATTACK_Y_POINT2;
			printf("右攻撃2\n");
		}
		//プレイヤーの3段目の攻撃
		else if (attackNumber == 3)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH3, ATTACK_HEIGHT3, CCollider::EColliderType::EPATTACK3);
			mX = *x + ATTACK_X_POINT3;
			mY = *y;
			printf("右攻撃3\n");
		}
		//スライムの攻撃
		else if (attackNumber == 4)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH_S, ATTACK_HEIGHT_S, CCollider::EColliderType::ESATTACK);
			mX = *x + ATTACK_X_POINT_S;
			mY = *y + ATTACK_Y_POINT_S;
		}
		//鬼の攻撃
		else if (attackNumber == 5)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH_O, ATTACK_HEIGHT_O, CCollider::EColliderType::EOATTACK);
			mX = *x + ATTACK_X_POINT_O;
			mY = *y;
		}
	}	
}

void CAttack::Update()
{
	//コライダの生存時間
	if (--mLife < 0)
	{
		mEnabled = false;
	}
}

//描画(無いとエラーになる)
void CAttack::Render()
{

}