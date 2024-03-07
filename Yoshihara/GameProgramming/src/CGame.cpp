#include "CGame.h"
#include "CApplication.h"

#define TEXTURE_ENEMY "Slime.png"
#define TEXTURE_BACKGROUND "Background.png"
#define ENEMY_STARTSET 600,100,60,40//x,y,w,h ‰¡:c=1.5:1
#define BACKGROUND_SET 400,300,400,300//x,y,w,h

CGame::CGame()
{	
	CApplication::GetTexture()->Load(TEXTURE_ENEMY);
	mpEnemy = new CEnemy(ENEMY_STARTSET,CApplication::GetTexture());
	//mpBackground = new CBackground(BACKGROUND_SET, CApplication::GetTexture());

}



void CGame::Update()
{
	//mpBackground->Render();
	mpEnemy->Render();
}



void CGame::Start()
{

}



CGame::~CGame()
{

}


