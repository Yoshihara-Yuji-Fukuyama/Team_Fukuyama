#include "CTaskManager.h"

//�f�t�H���g�R���X�g���N�^
CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
	mHeadObj.mpNextObj = &mTailObj;
	mTailObj.mpPrevObj = &mHeadObj;
	mHeadBackground.mpNextBackground = &mTailBackground;
	mTailBackground.mpPrevBackground = &mHeadBackground;
}

//�f�X�g���N�^
CTaskManager::~CTaskManager()
{
}

//���X�g�ɒǉ�
void CTaskManager::Add(CTask* addTask, bool isSort)
{
	if (!isSort)
	{
		//addTask�̗D��x���I�u�W�F�N�g�p�Ȃ�I�u�W�F�N�g�̃��X�g�ɒǉ�
		if (addTask->mPriority == (int)CTaskPriority::Object)
		{
			CTask* taskObj = mHeadObj.mpNextObj;
			//addTask�̎���taskObj
			addTask->mpNextObj = taskObj;
			//addTask�̑O��taskObj�̑O��
			addTask->mpPrevObj = taskObj->mpPrevObj;
			//addTask�̑O�̎���addTask��
			addTask->mpPrevObj->mpNextObj = addTask;
			//taskObj�̑O��addTask��
			taskObj->mpPrevObj = addTask;
		}
		//addTask�̗D��x���I�u�W�F�N�g�p�Ȃ�I�u�W�F�N�g�̃��X�g�ɒǉ�
		if (addTask->mPriority == (int)CTaskPriority::Field)
		{
			CTask* taskBackground = mHeadBackground.mpNextBackground;
			//addTask�̎���taskBackground
			addTask->mpNextBackground = taskBackground;
			//addTask�̑O��taskBackground�̑O��
			addTask->mpPrevBackground = taskBackground->mpPrevBackground;
			//addTask�̑O�̎���addTask��
			addTask->mpPrevBackground->mpNextBackground = addTask;
			//taskBackground�̑O��addTask��
			taskBackground->mpPrevBackground = addTask;
		}
	}
	//mHead�̎����猟��
	CTask* task = mHead.mpNext;

	//�D��x�̑傫�����ɑ}��
	//�D��x����������Ύ��̃^�X�N��
	//�D��x���������傫���Ȃ�����O�ɑ}��
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext;
	}
	//�D��x���������D��x���I�u�W�F�N�g�p�Ȃ珈�����Ԃ��傫�����ɓ����
	while (addTask->mPriority == task->mPriority && addTask->mPriority == (int)CTaskPriority::Object)
	{
		if (addTask->mSortOrder > task->mSortOrder)
		{
			//addTask�̎���task
			addTask->mpNext = task;
			//addTask�̑O��task�̑O��
			addTask->mpPrev = task->mpPrev;
			//addTask�̑O�̎���addTask��
			addTask->mpPrev->mpNext = addTask;
			//task�̑O��addTask��
			task->mpPrev = addTask;
			return;
		}
		task = task->mpNext;
	}
	//�D��x���������D��x���w�i�p�Ȃ珈�����Ԃ��傫�����ɓ����
	while (addTask->mPriority == task->mPriority && addTask->mPriority == (int)CTaskPriority::Field)
	{
		if (addTask->mSortOrder > task->mSortOrder)
		{
			//addTask�̎���task
			addTask->mpNext = task;
			//addTask�̑O��task�̑O��
			addTask->mpPrev = task->mpPrev;
			//addTask�̑O�̎���addTask��
			addTask->mpPrev->mpNext = addTask;
			//task�̑O��addTask��
			task->mpPrev = addTask;
			return;
		}
		task = task->mpNext;
	}
	//�D��x���傫���Ȃ�O�ɑ}��
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
void CTaskManager::Remove(CTask* removeTask, bool isSort)
{
	if (!isSort)
	{
		//�D��x���I�u�W�F�N�g�p�ł���΁A�I�u�W�F�N�g�̃��X�g�������菜��
		if (removeTask->mPriority == (int)CTaskPriority::Object)
		{
			//removeTask�̑O�̎����AremoveTask�̎��ɂ���
			removeTask->mpPrevObj->mpNextObj = removeTask->mpNextObj;
			//removeTask�̎��̑O���AremoveTask�̑O�ɂ���
			removeTask->mpNextObj->mpPrevObj = removeTask->mpPrevObj;
		}
		//�D��x���w�i�p�ł���΁A�w�i�̃��X�g�������菜��
		if (removeTask->mPriority == (int)CTaskPriority::Field)
		{
			//removeTask�̑O�̎����AremoveTask�̎��ɂ���
			removeTask->mpPrevBackground->mpNextBackground = removeTask->mpNextBackground;
			//removeTask�̎��̑O���AremoveTask�̑O�ɂ���
			removeTask->mpNextBackground->mpPrevBackground = removeTask->mpPrevBackground;
		}
	}
	//�^�X�N�̑O�̎����A�^�X�N�̎��ɂ���
	removeTask->mpPrev->mpNext = removeTask->mpNext;
	//�^�X�N�̎��̑O���A�^�X�N�̑O�ɂ���
	removeTask->mpNext->mpPrev = removeTask->mpPrev;
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

//�^�X�N�}�l�[�W���̃C���X�^���X
CTaskManager* CTaskManager::mpInstance = nullptr;

//�C���X�^���X�̎擾
CTaskManager* CTaskManager::GetInstance()
{
	//�C���X�^���X���Ȃ����
	if (mpInstance == nullptr)
	{
		//�C���X�^���X�𐶐�
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}

