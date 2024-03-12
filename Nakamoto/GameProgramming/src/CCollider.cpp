#include "CCollider.h"
#include "CCollisionManager.h"

CCollider::~CCollider()
{
	//コリジョンリストから削除
	CCollisionManager::GetInstance()->Remove(this);
}

CCollider::CCollider(CCharacter* parent,
	float* px, float* py, float w, float h)
{
	//コリジョンマネージャに追加
	CCollisionManager::GetInstance()->Add(this);

	//親の設定
	mpParent = parent;
	
	mpX = px;	//X座標
	mpY = py;	//Y座標
	mW = w;		//高さ
	mH = h;		//幅
}

CCharacter* CCollider::GetParent()
{
	return mpParent;
}

void CCollider::Render()
{
	glBegin(GL_QUADS);
	glVertex2f(*mpX - mW, *mpY - mH);
	glVertex2f(*mpX + mW, *mpY - mH);
	glVertex2f(*mpX + mW, *mpY + mH);
	glVertex2f(*mpX - mW, *mpY + mH);
	glEnd();
}

//衝突判定
bool CCollider::Collision(CCollider* m, CCollider* o)
{
	float x, y;
	if (m->mpX < o->mpX)
		x = o->mpX - m->mpX - m->mW - o->mW;
	else
		x = m->mpX - o->mpX - m->mW - o->mW;
	//0以上は衝突しない
	if (x >= 0.0f)
		return false;

	if (m->mpY < o->mpY)
		y = o->mpY - m->mpY - m->mH - o->mH;
	else
		y = m->mpY - o->mpY - m->mH - o->mH;
	//0以上は衝突しない
	if (y >= 0.0f)
		return false;

	//Yが短いか判定
	if (x < y)
	{
		//Y修正、Xは0
		x = 0.0f;
		//上の時
		if (m->mpY > o->mpY)
			y = -y;
	}
	else
	{
		//X修正、Yは0
		y = 0.0f;
		//上の時
		if (m->mpX > o->mpX)
			x = -x;
	}
	return true;
}