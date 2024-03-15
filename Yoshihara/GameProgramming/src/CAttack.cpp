#include "CAttack.h"
#include "CCollisionManager.h"
#include "CPlayer.h"

CAttack::CAttack(CCharacter* p, float* x, float* y)
	:mCollider(p, x, y, &mZ, 100, 200, true)
{
	
}

void CAttack::Collision()
{
	CCollisionManager::GetInstance()->Add(this);
}

void CAttack::Collision(CCharacter* m, CCharacter* o)
{
	
}