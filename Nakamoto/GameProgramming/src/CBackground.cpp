#include "CBackground.h"
#include "CGame.h"
#include "CPlayer.h"

//’è”‚Ì’è‹`
#define TEX_COORD_BACKGROUND 0,1920,1080,0   //ƒeƒNƒXƒ`ƒƒƒ}ƒbƒsƒ“ƒO
#define BACKGROUND_POSX 3840.0f              //ŽŸ‚ÌŽŸ‚Ì”wŒi‚ª¶¬‚³‚ê‚éÀ•W‚Ì‰ÁŒ¸ŽZ—p”’l
#define BACKGROUND_CLOUD_SPEED 0.5f          //‰_‚ÌƒXƒs[ƒh
#define BACKGROUND_BUILDING_SPEED 1.0f       //Œš•¨‚ÌƒXƒs[ƒh

//static•Ï”‚Ì’è‹`
CTexture CBackground::mTextureSky;
CTexture CBackground::mTextureCloudA;
CTexture CBackground::mTextureCloudB;
CTexture CBackground::mTextureCloudC;
CTexture CBackground::mTextureBuilding;
CTexture CBackground::mTextureRoad;

//ƒƒ\ƒbƒh‚Ì’è‹`
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

//”wŒi‚ÌƒfƒtƒHƒ‹ƒgƒRƒ“ƒXƒgƒ‰ƒNƒ^
CBackground::CBackground()
	:CCharacter((int)CTaskPriority::Field)
{
	mVx = CPlayer::GetInstance()->GetmVx();
}
//”wŒi‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^
CBackground::CBackground(float x, float y, float w, float h,
	CBackground* next2, CBackground* prev2, int sortOrder, float distanceX)
	: CBackground()
{
	X = distanceX;

	SetSortOrder(sortOrder);

	Set(x, y, w, h);

	//‰æ‘œ‚ÌÝ’è
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
	else if (mSortOrder == (int)EFieldSort::Building)
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

//XV
void CBackground::Update()
{
	CreateBackground(this, CPlayer::GetInstance());
	DeleteBackground(this, CPlayer::GetInstance());


	//”wŒi‚Ì‘¬“x’²®
	//‹ó
	if (mSortOrder == (int)EFieldSort::Sky)
	{
		SetX(CPlayer::GetInstance()->GetX());
	}
	//‰_
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
	//Œš•¨
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
	//“¹
	else
	{
	}
}

//”wŒi¶¬
void CBackground::CreateBackground(CBackground* background, CPlayer* player)
{
	//‚à‚µ‚±‚Ì”wŒi‚ÌXÀ•W‚ªƒvƒŒƒCƒ„[‚ÌXÀ•W‚æ‚è¬‚³‚¢
	//‚©‚ÂŽŸ‚Ì”wŒi‚ª¶¬‚³‚ê‚Ä‚¢‚È‚¢‚È‚ç
	if (background->GetX() < player->GetX() && NextBackground == nullptr)
	{
		if (mSortOrder == (int)EFieldSort::Sky)
		{
			//ŽŸ‚Ì”wŒi‚Ì¶¬
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Sky);
		}
		else if (mSortOrder == (int)EFieldSort::CloudA)
		{
			//ŽŸ‚Ì”wŒi‚Ì¶¬
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudA, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudB)
		{
			//ŽŸ‚Ì”wŒi‚Ì¶¬
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudB, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudC)
		{
			//ŽŸ‚Ì”wŒi‚Ì¶¬
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::CloudC, 1920);
		}
		else if (mSortOrder == (int)EFieldSort::Building)
		{
			//ŽŸ‚Ì”wŒi‚Ì¶¬
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Building, 1920);
		}
		else
		{
			//ŽŸ‚ÌŽŸ‚Ì”wŒi‚Ì¶¬
			NextBackground = new CBackground(background->GetX() + BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), nullptr, this, (int)EFieldSort::Road);
		}
	}

	//‚à‚µ‚±‚Ì”wŒi‚ÌXÀ•W‚ªƒvƒŒƒCƒ„[‚ÌXÀ•W‚æ‚è‘å‚«‚¢
	//‚©‚Â‘O‚Ì”wŒi‚ª¶¬‚³‚ê‚Ä‚¢‚È‚¢‚È‚ç
	if (background->GetX() > player->GetX() && PrevBackground == nullptr)
	{
		if (mSortOrder == (int)EFieldSort::Sky)
		{
			//‘O‚Ì”wŒi‚Ì¶¬
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Sky);
		}
		else if (mSortOrder == (int)EFieldSort::CloudA)
		{
			//‘O‚Ì”wŒi‚Ì¶¬
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudA, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudB)
		{
			//‘O‚Ì”wŒi‚Ì¶¬
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudB, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::CloudC)
		{
			//‘O‚Ì”wŒi‚Ì¶¬
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::CloudC, -1920);
		}
		else if (mSortOrder == (int)EFieldSort::Building)
		{
			//‘O‚Ì”wŒi‚Ì¶¬
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Building, -1920);
		}
		else
		{
			//‘O‚Ì”wŒi‚Ì¶¬
			PrevBackground = new CBackground(background->GetX() - BACKGROUND_POSX,
				background->GetY(), background->GetW(), background->GetH(), this, nullptr, (int)EFieldSort::Road);
		}
	}
}

//”wŒiíœ
void CBackground::DeleteBackground(CBackground* background, CPlayer* player)
{
	//‚à‚µ‚±‚Ì”wŒi‚ÌXÀ•W‚ªƒvƒŒƒCƒ„[‚ÌXÀ•W‚æ‚è¬‚³‚¢
	//‚©‚Â‘O‚Ì”wŒi‚ª¶¬‚³‚ê‚Ä‚¢‚é‚È‚ç
	if (background->GetX() < player->GetX() && PrevBackground != nullptr)
	{
		//‘O‚Ì‘O‚Ì”wŒi‚Ìíœ
		PrevBackground->SetEnabled(false);
		PrevBackground = nullptr;
	}
	//‚à‚µ‚±‚Ì”wŒi‚ÌXÀ•W‚ªƒvƒŒƒCƒ„[‚ÌXÀ•W‚æ‚è‘å‚«‚¢
	//‚©‚ÂŽŸ‚Ì”wŒi‚ª¶¬‚³‚ê‚Ä‚¢‚é‚È‚ç
	if (background->GetX() > player->GetX() && NextBackground != nullptr)
	{
		//ŽŸ‚ÌŽŸ‚Ì”wŒi‚Ìíœ
		NextBackground->SetEnabled(false);
		NextBackground = nullptr;
	}
}