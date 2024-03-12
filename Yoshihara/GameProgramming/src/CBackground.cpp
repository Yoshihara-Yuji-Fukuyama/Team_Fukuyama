#include "CBackground.h"
#include "CGame.h"

//定数の定義
#define TEX_COORD_BACKGROUND 0,1920,1080,0   //テクスチャマッピング
#define BACKGROUND_POSX 3840.0f              //次の次の背景が生成される座標の加減算用数値

//static変数の定義
CTexture CBackground::mTexture;

//メソッドの定義
CTexture* CBackground::GetTexture()
{
	return &mTexture;
}

//背景のデフォルトコンストラクタ
CBackground::CBackground()
	:CCharacter((int)CTaskPriority::Field)
{
}
//背景のコンストラクタ
CBackground::CBackground(float x, float y, float w, float h,
	CBackground* next2, CBackground* prev2)
	: CBackground()
{
	Set(x, y, w, h);

	Texture(GetTexture(), TEX_COORD_BACKGROUND);

	Next2Background = next2;
	Prev2Background = prev2;
}

//更新
void CBackground::Update()
{
	CreateBackground(this,CPlayer::GetInstance());
	DeleteBackground(this, CPlayer::GetInstance());
}

//背景生成
void CBackground::CreateBackground(CBackground* background, CPlayer* player)
{
	//もしこの背景のX座標がプレイヤーのX座標より小さい
	//かつ次の次の背景が生成されていないなら
	if (background->GetX() < player->GetX() && Next2Background == nullptr)
	{
		//次の次の背景の生成
		Next2Background = new CBackground(background->GetX() + BACKGROUND_POSX,
			background->GetY(), background->GetW(), background->GetH(), nullptr, this);
	}

	//もしこの背景のX座標がプレイヤーのX座標より大きい
	//かつ前の前の背景が生成されていないなら
	if (background->GetX() > player->GetX() && Prev2Background == nullptr)
	{
		//前の前の背景の生成
		Prev2Background = new CBackground(background->GetX() - BACKGROUND_POSX,
			background->GetY(), background->GetW(), background->GetH(), this, nullptr);
	}
}

//背景削除
void CBackground::DeleteBackground(CBackground* background, CPlayer* player)
{
	//もしこの背景のX座標がプレイヤーのX座標より小さい
	//かつ前の前の背景が生成されているなら
	if (background->GetX() < player->GetX() && Prev2Background != nullptr)
	{
		//前の前の背景の削除
		Prev2Background->SetEnabled(false);
		Prev2Background = nullptr;
	}
	//もしこの背景のX座標がプレイヤーのX座標より大きい
	//かつ次の次の背景が生成されているなら
	if (background->GetX() > player->GetX() && Next2Background != nullptr)
	{
		//次の次の背景の削除
		Next2Background->SetEnabled(false);
		Next2Background = nullptr;
	}
}