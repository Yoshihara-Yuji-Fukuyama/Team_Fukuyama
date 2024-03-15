#include "CCollider.h"
#include "CCollisionManager.h"
#include <stdio.h>

CCollider::CCollider()
{
}

CCollider::~CCollider()
{
	//コリジョンリストから削除
	CCollisionManager::GetInstance()->Remove(this);
}

CCollider::CCollider(CCharacter* parent,
	float* px, float* py,float* z, float w, float h ,bool attack)
	:CCollider()
{
	//コリジョンマネージャに追加
	CCollisionManager::GetInstance()->Add(this);
	printf("コライダー生成");

	//親の設定
	mpParent = parent;
	
	mpX = px;	//X座標
	if (attack)
	{
		mX = 100;
	}

	mpY = py;	//Y座標
	mpZ = z;
	mCW = w;	//高さ
	mCH = h;	//幅
}

CCharacter* CCollider::GetParent()
{
	return mpParent;
}

void CCollider::Render()
{
	glBegin(GL_QUADS);
	glVertex2f(*mpX - mCW, *mpY - mCH);
	glVertex2f(*mpX + mCW, *mpY - mCH);
	glVertex2f(*mpX + mCW, *mpY + mCH);
	glVertex2f(*mpX - mCW, *mpY + mCH);
	glEnd();
}

void CCollider::AttackCollider(CCharacter* parent, float x, float y, float w, float h)
{	
	//コリジョンマネージャに追加
	CCollisionManager::GetInstance()->Add(this,true);
}

#define HANI 150

//衝突判定
bool CCollider::Collision(CCollider* m, CCollider* o, float *ax, float *ay)
{
	//X座標の当たり判定
	if (*m->mpX < *o->mpX)
		*ax = *o->mpX - *m->mpX - m->mCW - o->mCW;
	else
		*ax = *m->mpX - *o->mpX - m->mCW - o->mCW;
	//0以上は衝突しない
	if (*ax >= 0.0f)
		return false;
	//Y座標の当たり判定
	if (*m->mpY < *o->mpY)
		*ay = *o->mpY - *m->mpY - m->mCH - o->mCH;
	else
		*ay = *m->mpY - *o->mpY - m->mCH - o->mCH;
	//0以上は衝突しない
	if (*ay >= 0.0f)
		return false;

	if (*o->mpZ > *m->mpY-HANI)
		return false;
	if (*o->mpZ < *m->mpY - 300)
		return false;

	//Yが短いか判定
	if (*ax < *ay)
	{
		//Y修正、Xは0
		*ax = 0.0f;
		//上の時
		if (*m->mpY > *o->mpY)
			*ay = -*ay;
	}
	else
	{
		//X修正、Yは0
		*ay = 0.0f;
		//上の時
		if (*m->mpX > *o->mpX)
			*ax = -*ax;
	}
	return true;
}