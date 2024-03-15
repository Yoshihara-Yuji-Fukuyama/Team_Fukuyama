#include "CAttack.h"
#include "CCollisionManager.h"
#include "CPlayer.h"

CAttack::CAttack(CCharacter* p, float* x, float* y,float *z)
	:mCollider(p, x, y, z, 100, 150, true)
{
	
}

void CAttack::Collision()
{
	CCollisionManager::GetInstance()->Add(this);
}

void CAttack::Collision(CCharacter* m, CCharacter* o)
{
	
}