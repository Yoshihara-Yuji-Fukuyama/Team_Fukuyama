#include "CRectangle.h"
#include "CApplication.h"
#include "CCollisionManager.h"

void CApplication::Start()
{
	mpGame = new CGame();

}

void CApplication::Update()
{
	mpGame->Update();

	CCollisionManager::GetInstance()->Collision();
	
	CCollisionManager::GetInstance()->Render();
}
