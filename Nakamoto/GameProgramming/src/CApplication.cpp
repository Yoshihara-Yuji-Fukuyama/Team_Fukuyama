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
	
	//コリジョンマネージャの衝突処理
	CCollisionManager::Instance()->Collision();

	//コライダの表示(確認用)
	CCollisionManager::Instance()->Render();


}
