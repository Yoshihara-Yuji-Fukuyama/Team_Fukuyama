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
	
	//�R���W�����}�l�[�W���̏Փˏ���
	CCollisionManager::Instance()->Collision();

	//�R���C�_�̕\��(�m�F�p)
	CCollisionManager::Instance()->Render();


}
