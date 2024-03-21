#include "CHeal.h"
#include "CPlayer.h"

#define HEAL_SIZE 100,100      //大きさ
#define HEAL_COLLIDER_SIZE 19,50 //判定大きさ
#define HEAL_SHADOW_SIZE 50,50   //影大きさ
#define HEAL_SHADOW_POSY 60      //影の高さ
#define TEX_HEAL 0,320,320,0 //回復アイテムのテスクチャマッピング
#define HEAL 0.2f            //回復割合
#define HEAL_BOTTOM 50      //足元計算用

//static変数の定義
CTexture CHeal::mTexture;

//staticメソッドの定義
CTexture* CHeal::GetTexture()
{
	return &mTexture;
}

CHeal::CHeal()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, HEAL_COLLIDER_SIZE, CCollider::EColliderType::EITEM)
{

}

CHeal::CHeal(float x, float y, CTexture* texture)
	:CHeal()
{
	Set(x, y, HEAL_SIZE);

	Texture(texture, TEX_HEAL);

	mLeg = HEAL_BOTTOM;
	//足元設定
	SetZ(GetY() - mLeg);
	//回復影
	mShadow = HEAL_SHADOW_POSY;
	mpShadow = new CShadow(GetX(), GetShadowPosY(), HEAL_SHADOW_SIZE);
}

void CHeal::Update()
{
	//処理順番を決定
	SetSortOrder(GetY() - mLeg);
}

void CHeal::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::EPLAYER:	//プレイヤーとの体のコライダとの衝突判定

		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			CPlayer::GetInstance()->HealHp(HEAL);
			SetEnabled(false);
		}
		break;
	}
}

CHeal::~CHeal()
{
	mpShadow->SetEnabled(false);
}