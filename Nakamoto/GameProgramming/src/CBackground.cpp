#include "CBackground.h"
#include "CGame.h"

//’è”‚Ì’è‹`
#define TEX_COORD_BACKGROUND 0,1920,1080,0   //ƒeƒNƒXƒ`ƒƒƒ}ƒbƒsƒ“ƒO
#define BACKGROUND_POSX 3840.0f              //ŽŸ‚ÌŽŸ‚Ì”wŒi‚ª¶¬‚³‚ê‚éÀ•W‚Ì‰ÁŒ¸ŽZ—p”’l

//static•Ï”‚Ì’è‹`
CTexture CBackground::mTexture;

//ƒƒ\ƒbƒh‚Ì’è‹`
CTexture* CBackground::GetTexture()
{
	return &mTexture;
}

//”wŒi‚ÌƒfƒtƒHƒ‹ƒgƒRƒ“ƒXƒgƒ‰ƒNƒ^
CBackground::CBackground()
	:CCharacter((int)CTaskPriority::Field)
{
}
//”wŒi‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^
CBackground::CBackground(float x, float y, float w, float h,
	CBackground* next2, CBackground* prev2)
	: CBackground()
{
	Set(x, y, w, h);

	Texture(GetTexture(), TEX_COORD_BACKGROUND);

	Next2Background = next2;
	Prev2Background = prev2;
}

//XV
void CBackground::Update()
{
	CreateBackground(this, CPlayer::GetInstance());
	DeleteBackground(this, CPlayer::GetInstance());
}

//”wŒi¶¬
void CBackground::CreateBackground(CBackground* background, CPlayer* player)
{
	//‚à‚µ‚±‚Ì”wŒi‚ÌXÀ•W‚ªƒvƒŒƒCƒ„[‚ÌXÀ•W‚æ‚è¬‚³‚¢
	//‚©‚ÂŽŸ‚ÌŽŸ‚Ì”wŒi‚ª¶¬‚³‚ê‚Ä‚¢‚È‚¢‚È‚ç
	if (background->GetX() < player->GetX() && Next2Background == nullptr)
	{
		//ŽŸ‚ÌŽŸ‚Ì”wŒi‚Ì¶¬
		Next2Background = new CBackground(background->GetX() + BACKGROUND_POSX,
			background->GetY(), background->GetW(), background->GetH(), nullptr, this);
	}

	//‚à‚µ‚±‚Ì”wŒi‚ÌXÀ•W‚ªƒvƒŒƒCƒ„[‚ÌXÀ•W‚æ‚è‘å‚«‚¢
	//‚©‚Â‘O‚Ì‘O‚Ì”wŒi‚ª¶¬‚³‚ê‚Ä‚¢‚È‚¢‚È‚ç
	if (background->GetX() > player->GetX() && Prev2Background == nullptr)
	{
		//‘O‚Ì‘O‚Ì”wŒi‚Ì¶¬
		Prev2Background = new CBackground(background->GetX() - BACKGROUND_POSX,
			background->GetY(), background->GetW(), background->GetH(), this, nullptr);
	}
}

//”wŒiíœ
void CBackground::DeleteBackground(CBackground* background, CPlayer* player)
{
	//‚à‚µ‚±‚Ì”wŒi‚ÌXÀ•W‚ªƒvƒŒƒCƒ„[‚ÌXÀ•W‚æ‚è¬‚³‚¢
	//‚©‚Â‘O‚Ì‘O‚Ì”wŒi‚ª¶¬‚³‚ê‚Ä‚¢‚é‚È‚ç
	if (background->GetX() < player->GetX() && Prev2Background != nullptr)
	{
		//‘O‚Ì‘O‚Ì”wŒi‚Ìíœ
		Prev2Background->SetEnabled(false);
		Prev2Background = nullptr;
	}
	//‚à‚µ‚±‚Ì”wŒi‚ÌXÀ•W‚ªƒvƒŒƒCƒ„[‚ÌXÀ•W‚æ‚è‘å‚«‚¢
	//‚©‚ÂŽŸ‚ÌŽŸ‚Ì”wŒi‚ª¶¬‚³‚ê‚Ä‚¢‚é‚È‚ç
	if (background->GetX() > player->GetX() && Next2Background != nullptr)
	{
		//ŽŸ‚ÌŽŸ‚Ì”wŒi‚Ìíœ
		Next2Background->SetEnabled(false);
		Next2Background = nullptr;
	}
}