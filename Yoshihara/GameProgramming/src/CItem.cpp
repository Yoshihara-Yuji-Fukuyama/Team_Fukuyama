#include "CItem.h"

#define TEX_HEAL 0,320,320,0

//static変数の定義
CTexture CItem::mTexture;

//staticメソッドの定義
CTexture* CItem::GetTexture()
{
	return &mTexture;
}

CItem::CItem()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, 10, 10, CCollider::EColliderType::EITEM)
{

}

CItem::CItem(float x, float y, float w, float h, CTexture* texture)
{
	Set(x, y, w, h);

	Texture(texture, TEX_HEAL);

}

void CItem::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::EPLAYER:	//スライムの体のコライダとの衝突判定

		//コライダのmとoが衝突しているか判定しているか判定
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//プレイヤーとの衝突判定を実行(めり込まない処理)
			//SetX(GetX() + ax);
			//調整中
			//SetY(GetY() + ay);


		}
		break;
	}
}