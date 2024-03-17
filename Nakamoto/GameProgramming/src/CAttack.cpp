#include "CAttack.h"
#include "CCollisionManager.h"

#define LIFE 50

CAttack::CAttack(CCharacter* p, float* x, float* y, float* z, float mvx)
	:CCharacter(*z)
	,mLife(LIFE)
{
	mCollider.SetCollider(this, &mX, &mY, &mZ, 70, 120, CCollider::EColliderType::EPATTACK1);
	
	mVx = mvx;
	if (mVx < 0) 
	{
		mX = *x - 200;
		mY = *y + 80;
		mZ = *z;
	}
	else
	{
		mX = *x + 200;
		mY = *y + 80;
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

//•`‰æ(–³‚¢‚ÆƒGƒ‰[‚É‚È‚é)
void CAttack::Render()
{

}