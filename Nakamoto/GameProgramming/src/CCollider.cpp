#include "CCollider.h"
#include "CCollisionManager.h"

//デフォルトコンストラクタ
CCollider::CCollider()
{
	
}
//~デストラクタ
CCollider::~CCollider()
{
	//コリジョンリストから削除
	CCollisionManager::Instance()->Remove(this);
}

//コンストラクタ
CCollider::CCollider(CCharacter* parent,
	float &x, float &y, float w, float h)
{
	//衝突コライダーに追加
	CCollisionManager::Instance()->Add(this);

	//親の設定
	mpParent = parent;

	mpXC = &x;
	mpYC = &y;
	mWC = w;
	mHC = h;

}

//親クラスの取得
CCharacter* CCollider::GetParent()
{
	return mpParent;
}

//衝突処理
bool CCollider::Collision(CCollider* m, CCollider* o, float* ax, float* ay)
{
	if (m->mpXC < o->mpXC)
		*ax = o->mpXC - m->mpXC - m->mWC - o->mWC;
	else
		*ax = m->mpXC - o->mpXC - m->mWC - o->mWC;
	//0以上は衝突しない
	if (*ax >= 0.0f)
		return false;

	if (m->mpYC < o->mpYC)
		*ay = o->mpYC - m->mpYC - m->mHC - o->mHC;
	else
		*ay = m->mpYC - o->mpYC - m->mHC - o->mHC;
	//0以上は衝突しない
	if (*ay >= 0.0f)
		return false;

	//Yが短いか判定
	if (*ax < *ay)
	{
		//Y修正、Xは0
		*ax = 0.0f;
		//上の時
		if (m->mpYC > o->mpYC)
			*ay = -*ay;
	}
	else
	{
		//X修正、Yは0
		*ay = 0.0f;
		//右の時
		if (m->mpXC > o->mpXC)
			*ax = -*ax;
	}
	return true;
}

void CCollider::ChanegePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this);	//一旦削除
	CCollisionManager::Instance()->Add(this);
}

//描画
void CCollider::Render()
{
	//四角形で描写
	glBegin(GL_QUADS);
	glVertex2f(*mpXC - mWC, *mpYC - mHC);
	glVertex2f(*mpXC + mWC, *mpYC - mHC);
	glVertex2f(*mpXC + mWC, *mpYC + mHC);
	glVertex2f(*mpXC - mWC, *mpYC + mHC);
	glEnd();
}