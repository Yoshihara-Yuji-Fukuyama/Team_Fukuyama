#include "CObjectBase.h"

//コンストラクタ
CObjectBase::CObjectBase(const CVector2D& pos)
	:CTask((int)CTaskPriority::Object)
	,mPos(pos)
	
{

}

//デストラクタ
CObjectBase::~CObjectBase()
{

}

//オブジェクトの座標を設定
void CObjectBase::SetPos(const CVector2D& pos)
{
	mPos = pos;
}

//オブジェクトの座標を取得
const CVector2D& CObjectBase::GetPos() const
{
	return mPos;
}

