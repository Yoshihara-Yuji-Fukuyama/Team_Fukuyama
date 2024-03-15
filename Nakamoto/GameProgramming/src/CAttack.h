#pragma once
#include "CCharacter.h"
#include "CCollider.h"

class CAttack :public CCharacter
{
public:
	CAttack(CCharacter* p,float *x,float *y,float *z);

	//void Set(float w, float h);

	//void Update();

	void Collision();

	void Collision(CCharacter* m, CCharacter* o);

private:
	CCollider mCollider;
};