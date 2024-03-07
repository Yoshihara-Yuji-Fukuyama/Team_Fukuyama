#include "ObjectBase.h"

//コンストラクタ
ObjectBase::ObjectBase(const CVector2D& pos)
	:CTask((int)CTaskPrio::Object)
	,mPos(pos)
{

}

//デストラクタ
ObjectBase::~ObjectBase()
{

}

//オブジェクトの座標を設定
void ObjectBase::SetPos(const CVector2D& pos)
{
	mPos = pos;
}

//オブジェクトの座標を取得
const CVector2D& ObjectBase::GetPos()const
{
	return mPos;
}
