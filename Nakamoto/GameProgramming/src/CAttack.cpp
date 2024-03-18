#include "CAttack.h"
#include "CCollisionManager.h"

//確認用 削除予定
#include <stdio.h>


#define LIFE 50

#define ATTACK_X_POINT 200	//攻撃コライダの生成位置のX座標の加算値

#define ATTACK_Y_POINT1 80	//1段目の攻撃コライダの生成位置のY座標の加算値

//エラーが出る
//#define ATTACK_Y_POINT2 20　//2段目の攻撃コライダの生成位置のY座標の加算値

#define ATTACK_WIDTH 70	//攻撃コライダの幅

#define ATTACK_HEIGHT1 120	//1段目の高さ
#define ATTACK_HEIGHT2 150	//2段目の高さ
#define ATTACK_HEIGHT3 200	//3段目の高さ


CAttack::CAttack(CCharacter* parent, float* x, float* y, float* z, float mvx, int attackNumber)
	:CCharacter(*z)
	,mLife(LIFE)
{
	mZ = *z;
	mVx = mvx;
	
	if (mVx < 0) 
	{
		//左向き
		if (attackNumber == 1)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT1, CCollider::EColliderType::EPATTACK1);
			mX = *x - ATTACK_X_POINT;
			mY = *y + ATTACK_Y_POINT1;
			printf("左攻撃1\n");
		}
		else if (attackNumber == 2)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT2, CCollider::EColliderType::EPATTACK2);
			mX = *x - ATTACK_X_POINT;
			mY = *y + 20;
			printf("左攻撃2\n");
		}
		else if (attackNumber == 3)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT3, CCollider::EColliderType::EPATTACK3);
			mX = *x - ATTACK_X_POINT;
			mY = *y;
			printf("左攻撃3\n");
		}
		else if (attackNumber == 4)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, 150, 100, CCollider::EColliderType::ESATTACK);
			mX = *x;
			mY = *y;
		}
		else if (attackNumber == 5)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT3, CCollider::EColliderType::EOATTACK);
			mX = *x - ATTACK_X_POINT;
			mY = *y;
		}
	}
	else
	{
		//右向き
		if (attackNumber == 1)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT1, CCollider::EColliderType::EPATTACK1);
			mX = *x + ATTACK_X_POINT;
			mY = *y + ATTACK_Y_POINT1;
			printf("右攻撃1\n");
		}
		else if (attackNumber == 2)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT2, CCollider::EColliderType::EPATTACK2);
			mX = *x + ATTACK_X_POINT;
			mY = *y + 20;
			printf("右攻撃2\n");
		}
		else if (attackNumber == 3)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT3, CCollider::EColliderType::EPATTACK3);
			mX = *x + ATTACK_X_POINT;
			mY = *y;
			printf("右攻撃3\n");
		}
		else if (attackNumber == 4)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, 200, 20, CCollider::EColliderType::ESATTACK);
			mX = *x + ATTACK_X_POINT;
			mY = *y;
		}
		else if (attackNumber == 5)
		{
			mCollider.SetCollider(this, &mX, &mY, &mZ, ATTACK_WIDTH, ATTACK_HEIGHT3, CCollider::EColliderType::EOATTACK);
			mX = *x + ATTACK_X_POINT;
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

void CAttack::Collision(CCharacter* m, CCharacter* o)
{
	
}

//描画(無いとエラーになる)
void CAttack::Render()
{

}