#include "CRectangle.h"
#include "CApplication.h"

void CApplication::Start()
{
	mpGame = new CGame();
}


void CApplication::Update()
{
	mpGame->Update();
}