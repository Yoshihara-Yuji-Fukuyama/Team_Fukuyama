#include "CAttack.h"
#include "CCollisionManager.h"

#define LIFE 50

CAttack::CAttack(CCharacter* p, float* x, float* y, float* z, float mvx )
	:CCharacter(*z)
	, mCollider(this, &mX, &mY, &mZ, 50, 150, CCollider::EColliderType::EPATTACK1, true)
	,mLife(LIFE)
{
	mVx = mvx;
	if (mVx < 0) 
	{
		mX = *x - 200;
		mY = *y + 50;
		mZ = *z;
	}
	else
	{
		mX = *x + 200;
		mY = *y + 50;
		mZ = *z;
	}
}

void CAttack::Update()
{
	if (--mLife < 0)
	{
		mEnabled = false;
	}
	
}

void CAttack::Collision(CCharacter* m, CCharacter* o)
{
	
}

void CAttack::Render()
{

}