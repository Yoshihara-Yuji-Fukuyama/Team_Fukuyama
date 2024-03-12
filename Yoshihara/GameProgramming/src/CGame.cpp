#include "CGame.h"
#include "CApplication.h"
#include "CCamera.h"
#include "main.h"

#define TEXTURE_PLAYER "Player.png"          //ƒvƒŒƒCƒ„[‰æ‘œ
#define TEXTURE_BACKGROUND "Background.png"  //”wŒi‰æ‘œ
#define TEXTURE_ENEMY "Slime.png"            //ƒXƒ‰ƒCƒ€‰æ‘œ

#define ENEMY_STARTSET 1700.0f,400.0f,300.0f,300.0f//x,y,w,h@“G‚Ì‰ŠúˆÊ’u
#define BACKGROUND_SET1 960.0f,540.0f,960.0f,540.0f//x,y,w,h@”wŒi1‚Ì‰ŠúˆÊ’u
#define BACKGROUND_SET2 2880.0f,540.0f,960.0f,540.0f//x,y,w,h ”wŒi2‚Ì‰ŠúˆÊ’u

CGame::CGame()
{		
	//ƒeƒNƒXƒ`ƒƒ‚ðƒ[ƒh
	CPlayer::GetTexture()->Load(TEXTURE_PLAYER);
	CEnemy::GetTexture()->Load(TEXTURE_ENEMY);
	CBackground::GetTexture()->Load(TEXTURE_BACKGROUND);

	//”wŒi¶¬
	new CBackground(BACKGROUND_SET1, nullptr, nullptr);
	new CBackground(BACKGROUND_SET2, nullptr, nullptr);
	//ƒvƒŒƒCƒ„[¶¬
	CPlayer::GetInstance();
	//“G¶¬
	new CEnemy(ENEMY_STARTSET);

}



void CGame::Update()
{	//íœ
	CTaskManager::GetInstance()->Delete();
	//XV
	CTaskManager::GetInstance()->Update();
	//ƒJƒƒ‰‚ðÝ’è
	SetCamera();
	//•`‰æ
	CTaskManager::GetInstance()->Render();
	CCamera::End();
}



void CGame::Start()
{

}



CGame::~CGame()
{
	//‚·‚×‚Äíœ
	CTaskManager::GetInstance()->AllDelete();
}

//ƒJƒƒ‰‚ðÝ’è
void CGame::SetCamera()
{
	float x = CPlayer::GetInstance()->GetX();

	CCamera::SetCamera(x - WINDOW_WIDTH / 2
		, x + WINDOW_WIDTH / 2
		, 0
		, WINDOW_HEIGHT);
}
