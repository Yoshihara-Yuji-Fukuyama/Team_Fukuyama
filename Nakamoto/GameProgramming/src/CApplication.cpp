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
	
	//コライダの表示(確認用)
	CCollisionManager::GetInstance()->Render();
}
