#include "CCharacter.h"
#include "CTaskManager.h"

//テクスチャの設定
void CCharacter::Texture(CTexture* pTexture, int left, int right, int bottom, int top)
{
	mpTexture = pTexture;

	mLeft = left;

	mRight = right;

	mBottom = bottom;

	mTop = top;
}

//描画
void CCharacter::Render()
{
	mpTexture->DrawImage(
		GetX() - GetW(),
		GetX() + GetW(),
		GetY() - GetH(),
		GetY() + GetH(),
		mLeft, mRight, mBottom, mTop
	);
}

//デフォルトコンストラクタ
CCharacter::CCharacter()
	: mpTexture(nullptr)
	, mLeft(0.0f), mRight(0.0f), mBottom(0.0f), mTop(0.0f)
{
	//CTaskManager::GetInstance()->Add(this);
}

//コンストラクタ
CCharacter::CCharacter(int priority)
	: mpTexture(nullptr)
	, mLeft(0.0f), mRight(0.0f), mBottom(0.0f), mTop(0.0f)
{
	mPriority = priority;
	CTaskManager::GetInstance()->Add(this);
}

//デストラクタ
//削除されたらリストからも削除する
CCharacter::~CCharacter()
{
	CTaskManager::GetInstance()->Remove(this);
}

//mpTextureを返す
CTexture* CCharacter::GetTexture()
{
	return mpTexture;
}

//有効フラグを設定
void CCharacter::SetEnabled(bool isEnabled)
{
	mEnabled = isEnabled;
}
//有効フラグを返す
bool CCharacter::GetEnabled()
{
	return mEnabled;
}

//処理順番を設定
void CCharacter::SetSortOrder(float order)
{
	mSortOrder = order;
	CTaskManager::GetInstance()->Remove(this, true);
	CTaskManager::GetInstance()->Add(this, true);
}
//処理順番を取得
float CCharacter::GetSortOrder()
{
	return mSortOrder;
}

//足元の座標を取得
float CCharacter::GetUnderPosY()
{
	if (mState != EState::EJUMP)
	{
		mUnderPosY = GetY() - mLeg;
	}
	else
	{
		mUnderPosY = mJump;
	}
	return mUnderPosY;
}

float CCharacter::GetmVx()
{
	return mVx;
}