#include "CBackground.h"
#include "CGame.h"
#include "CPlayer.h"

//定数の定義
#define TEX_COORD_BACKGROUND 0,1920,1080,0   //テクスチャマッピング
#define BACKGROUND_POSX 3840.0f              //次の次の背景が生成される座標の加減算用数値
#define BACKGROUND_CLOUD_SPEED 0.5f          //雲のスピード
#define BACKGROUND_BUILDING_SPEED 1.0f       //建物のスピード

//static変数の定義
CTexture CBackground::mTextureSky;
CTexture CBackground::mTextureCloudA;
CTexture CBackground::mTextureCloudB;
CTexture CBackground::mTextureCloudC;
CTexture CBackground::mTextureBuilding;
CTexture CBackground::mTextureRoad;

//メソッドの定義
CTexture* CBackground::GetTextureSky()
{
	return &mTextureSky;
}
CTexture* CBackground::GetTextureCloudA()
{
	return &mTextureCloudA;
}
CTexture* CBackground::GetTextureCloudB()
{
	return &mTextureCloudB;
}
CTexture* CBackground::GetTextureCloudC()
{
	return &mTextureCloudC;
}
CTexture* CBackground::GetTextureBuilding()
{
	return &mTextureBuilding;
}
CTexture* CBackground::GetTextureRoad()
{
	return &mTextureRoad;
}

//背景のデフォルトコンストラクタ
CBackground::CBackground()
	:CCharacter((int)CTaskPriority::Field)
{
	mVx = CPlayer::GetInstance()->GetmVx();
}
//背景のコンストラクタ
CBackground::CBackground(float x, float y, float w, float h,
	CBackground* next2, CBackground* prev2, int sortOrder, float distanceX)
	: CBackground()
{
	X = distanceX;

	SetSortOrder(sortOrder);

	Set(x, y, w, h);
	
	//画像の設定
	if (mSortOrder == (int)EFieldSort::Sky)
	{
		Texture(GetTextureSky(), TEX_COORD_BACKGROUND);
	}
	else if (mSortOrder == (int)EFieldSort::CloudA)
	{
		Texture(GetTextureCloudA(), TEX_COORD_BACKGROUND);
	}
	else if (mSortOrder == (int)EFieldSort::CloudB)
	{
		Texture(GetTextureCloudB(), TEX_COORD_BACKGROUND);
	}
	else if (mSortOrder == (int)EFieldSort::CloudC)
	{
		Texture(GetTextureCloudC(), TEX_COORD_BACKGROUND);
	}
	else if(mSortOrder == (int)EFieldSort::Building)
	{
		Texture(GetTextureBuilding(), TEX_COORD_BACKGROUND);
	}
	else
	{
		Texture(GetTextureRoad(), TEX_COORD_BACKGROUND);
	}


	NextBackground = next2;
	PrevBackground = prev2;
}

//更新
void CBackground::Update()
{
	CreateBackground(this,CPlayer::GetInstance());
	DeleteBackground(this, CPlayer::GetInstance());


	//背景の速度調整
	//空
	if (mSortOrder == (int)EFieldSort::Sky)
	{
		SetX(CPlayer::GetInstance()->GetX());
	}
	//雲
	else if (mSortOrder == (int)EFieldSort::CloudA || mSortOrder == (int)EFieldSort::CloudB || mSortOrder == (int)EFieldSort::CloudC)
	{
		if (CPlayer::GetInstance()->GetMoveX())
		{
			if (CPlayer::GetInstance()->GetmVx() < 0)
			{
				X = X + BACKGROUND_CLOUD_SPEED;
			}
			else
			{
				X = X - BACKGROUND_CLOUD_SPEED;
			}
		}
		SetX(CPlayer::GetInstance()->GetX() + X);
	}
	//建物
	else if (mSortOrder == (int)EFieldSort::Building)
	{
		if (CPlayer::GetInstance()->GetMoveX())
		{
			if (CPlayer::GetInstance()->GetmVx() < 0)
			{
				X = X + BACKGROUND_BUILDING_SPEED;
			}
			else
			{
				X = X - BACKGROUND_BUILDING_SPEED;
			}
		}
		SetX(CPlayer::GetInstance()->GetX() + X);

	}
	//道
	else
	{
	}
}

//背景生成
void CBackground::CreateBackground(CBackground* background, CPlayer* player)
{
	//もしこの背景のX座標がプレイヤーのX座標より小さい
	//かつ次の背景が生成されていないなら
	if (background->GetX() < player->GetX() && NextBackground == nullptr)
	{
		if (mSortOrder == (int)EFieldSort::Sky)
		{
			//次の背景の生成
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Sky);
		}
		else if (mSortOrder == (int)EFieldSort::CloudA)
		{
			//次の背景の生成
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudA, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudB)
		{
			//次の背景の生成
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudB, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudC)
		{
			//次の背景の生成
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudC, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::Building)
		{
			//次の背景の生成
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Building, 1920);
		}
		else
		{
			//次の次の背景の生成
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Road);
		}
	}

	//もしこの背景のX座標がプレイヤーのX座標より大きい
	//かつ前の背景が生成されていないなら
	if (background->GetX() > player->GetX() && PrevBackground == nullptr)
	{
		if (mSortOrder == (int)EFieldSort::Sky)
		{
			//前の背景の生成
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Sky);
		}
		else if (mSortOrder == (int)EFieldSort::CloudA)
		{
			//前の背景の生成
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudA, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudB)
		{
			//前の背景の生成
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudB, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudC)
		{
			//前の背景の生成
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudC, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::Building)
		{
			//前の背景の生成
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Building, -1920);
		}
		else
		{
			//前の背景の生成
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Road);
		}
	}
}

//背景削除
void CBackground::DeleteBackground(CBackground* background, CPlayer* player)
{
	//もしこの背景のX座標がプレイヤーのX座標より小さい
	//かつ前の背景が生成されているなら
	if (background->GetX() < player->GetX() && PrevBackground != nullptr)
	{
		//前の前の背景の削除
		PrevBackground->SetEnabled(false);
		PrevBackground = nullptr;
	}
	//もしこの背景のX座標がプレイヤーのX座標より大きい
	//かつ次の背景が生成されているなら
	if (background->GetX() > player->GetX() && NextBackground != nullptr)
	{
		//次の次の背景の削除
		NextBackground->SetEnabled(false);
		NextBackground = nullptr;
	}
}