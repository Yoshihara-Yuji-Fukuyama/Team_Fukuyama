#include "CCollisionManager.h"
#include "CCollider.h"

//�R���C�_�}�l�[�W���̃C���X�^���X
CCollisionManager* CCollisionManager::mpInstance = nullptr;
//�C���X�^���X�̎擾
CCollisionManager* CCollisionManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}

//�Փˏ���
void CCollisionManager::Collision()
{
	//���݈ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
	//�Ō�܂ŗ�����I������
	while (task->mpNext) 
	{
		//���݈ʒu�̎������߂�
		CCollider* next = (CCollider*)task->mpNext;
		//���|�C���^��0�ɂȂ�����I��
		while (next->mpNext) {
			//�e�̏Փˏ������Ăяo��
			//�����̏Փˏ���
			if (task->mpParent)
				task->mpParent->Collision(task, next);
			//����̏Փˏ���
			if (next->mpParent)
				next->mpParent->Collision(next, task);
			//�������߂�
			next = (CCollider*)next->mpNext;
		}
		//���݈ʒu�����ɂ���
		task = task = (CCollider*)task->mpNext;
	}
}