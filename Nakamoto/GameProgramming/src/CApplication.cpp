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
	
	//�R���C�_�̕\��(�m�F�p)
	CCollisionManager::GetInstance()->Render();
}
