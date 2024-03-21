#include "CCollider.h"
#include "CCollisionManager.h"
#include "CCharacter.h"
#include "CEnemy.h"
//確認用 削除予定
#include <iostream>

#define HANI 60

CCollider::CCollider()
	:mpParent(nullptr)
{
}

CCollider::~CCollider()
{
	//コリジョンリストから削除
	CCollisionManager::GetInstance()->Remove(this);
}

CCollider::CCollider(CCharacter* parent,
	float* px, float* py, float* z, float w, float h, EColliderType cType)
	:CCollider()
{
	//コリジョンマネージャに追加
	CCollisionManager::GetInstance()->Add(this);

	printf("プレイヤーのコライダー生成\n");//確認用 削除予定

	//親の設定
	mpParent = parent;

	mpX = px;	//X座標
	mpY = py;	//Y座標
	mLeg = z;	//足元の座標
	mCW = w;	//高さ
	mCH = h;	//幅
	mColliderType = cType;	//コライダの種類

}

void CCollider::SetCollider(CCharacter* parent,
	float* px, float* py, float* z, float w, float h, EColliderType cType)
{
	//コリジョンマネージャに追加
	CCollisionManager::GetInstance()->Add(this);

	//親の設定
	mpParent = parent;

	mpX = px;	//X座標
	mpY = py;	//Y座標
	mLeg = z;	//足元の座標
	mCW = w;	//高さ
	mCH = h;	//幅
	mColliderType = cType;	//コライダの種類

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

CCollider::EColliderType CCollider::GetCType()
{
	return mColliderType;
}


//衝突判定
bool CCollider::Collision(CCollider* m, CCollider* o, float* ax, float* ay)
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
	//奥行で衝突しているか
	if (*o->mLeg < *m->mLeg - HANI)
		return false;
	if (*o->mLeg > *m->mLeg + HANI)
		return false;

	//Yが短いか判定
	if (*ax < *ay)
	{
		//Y修正、Xは0
		*ax = 0.0f;
		*ay = *o->mLeg - *m->mLeg - HANI;
		//上の時
		if (*m->mLeg > *o->mLeg)
			*ay = *o->mLeg - *m->mLeg + HANI;
	}
	else
	{
		//X修正、Yは0
		*ay = 0.0f;
		//右の時
		if (*m->mpX > *o->mpX)
			*ax = -*ax;
	}
	return true;
}

float CCollider::GetmpY()
{
	return *mpY;
}