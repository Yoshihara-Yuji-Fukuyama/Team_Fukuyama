#include "CTaskManager.h"

//�f�t�H���g�R���X�g���N�^
CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}

//�f�X�g���N�^
CTaskManager::~CTaskManager() {}

//���X�g�ɒǉ�
void CTaskManager::Add(CTask* addTask)
{
	//mTail�̑O�ɒǉ�
	CTask* task = &mTail;
	//addTask�̎���task
	addTask->mpNext = task;
	//addTask�̑O��task�̑O��
	addTask->mpPrev = task->mpPrev;
	//addTask�̑O�̎���addTask��
	addTask->mpPrev->mpNext = addTask;
	//task�̑O��addTask��
	task->mpPrev = addTask;
}

//���X�g����폜
void CTaskManager::Remove(CTask* task)
{
	//�^�X�N�̑O�̎����A�^�X�N�̎��ɂ���
	task->mpPrev->mpNext = task->mpNext;
	//�^�X�N�̎��̑O���A�^�X�N�̑O�ɂ���
	task->mpNext->mpPrev = task->mpPrev;
}

//�^�X�N�̍폜
void CTaskManager::Delete()
{
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		CTask* del = task;
		//����
		task = task->mpNext;
		//mEnabled��false�Ȃ�폜
		if (del->mEnabled == false)
		{
			delete del;
		}
	}
}

//�^�X�N�̑S�폜
void CTaskManager::AllDelete()
{
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		CTask* del = task;
		//����
		task = task->mpNext;
		//�폜
		delete del;
	}
}

//�X�V
void CTaskManager::Update()
{
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		//�X�V�������Ă�
		task->Update();
		//����
		task = task->mpNext;
	}
}

//�`��
void CTaskManager::Render()
{
	//�擪����Ō�܂ŌJ��Ԃ�
	CTask* task = mHead.mpNext;
	while (task->mpNext)
	{
		//�`�揈�����Ă�
		task->Render();
		//����
		task = task->mpNext;
	}
}