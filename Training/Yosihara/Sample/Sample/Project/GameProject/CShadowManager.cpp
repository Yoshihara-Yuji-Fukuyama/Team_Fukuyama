#include "CShadowManager.h"
#include "CTaskManager.h"
#include "CObjectBase.h"

//�R���X�g���N�^
CShadowManager::CShadowManager()
	:CTask((int)CTaskPriority::Shadow)
	, mpImage(nullptr)
{
	//�e�̉摜��ǂݍ���
	mpImage = CImage::CreateImage("shadow.png");
	mpImage->SetCenter(52.0f, 16.0f);
		
}

//�f�X�g���N�^
CShadowManager::~CShadowManager()
{
	//�e�̉摜�f�[�^���폜
	delete mpImage;
}

//�X�V
void CShadowManager::Update()
{

}

//�`��
void CShadowManager::Render()
{
	//�I�u�W�F�N�g���X�g���擾
	auto& objects = CTaskManager::GetObjectList();
	for (CTask* task : objects)
	{
		CObjectBase* obj = dynamic_cast<CObjectBase*>(task);
		if (obj == nullptr)continue;

		//�e�I�u�W�F�N�g�̍��W�ɉe�̉摜��`��
		mpImage->SetPos(obj->GetPos());
		mpImage->Draw();
	}
}