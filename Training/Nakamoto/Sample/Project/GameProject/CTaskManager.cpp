#include "CTaskManager.h"
#include "CTask.h"
#include "ObjectBase.h"

//�^�X�N�̃��X�g���`
std::list<CTask*>  CTaskManager::mTaskList;
//�I�u�W�F�N�g�̃��X�g���`
std::list<CTask*> CTaskManager::mObjectList;

//�R���X�g���N�^
CTaskManager::CTaskManager()
{

}

//�f�X�g���N�^
CTaskManager::~CTaskManager()
{

}

//�^�X�N�����X�g�ɒǉ�
void CTaskManager::Add(CTask* add, bool isSort)
{
	//�\�[�g���̃^�X�N�ǉ��̌Ăяo���łȂ���΁A
	if (!isSort)
	{
		//�ǉ�����^�X�N�̗D��x���I�u�W�F�N�g�p�ł���΁B
		//�I�u�W�F�N�g���X�g�ɒǉ�
		if (add->mPrio == (int)CTaskPrio::Object)
		{
			mObjectList.push_back(add);
		}
	}

	auto itr = mTaskList.begin();
	auto end = mTaskList.end();
	while (itr != end)
	{
		CTask* task = *itr;
		//�ǉ�����^�X�N�̗D��x < ���݂̃^�X�N�̗D��x�Ȃ�΁A
		//���̈ʒu�Ƀ^�X�N��ǉ�
		if (add->mPrio < task->mPrio)
		{
			mTaskList.insert(itr, add);
			return;
		}
		//�ǉ�����^�X�N�̗D��x�ƌ��݂̃^�X�N�̗D��x�������Ȃ�΁A
		else if (add->mPrio == task->mPrio) {
			//�������Ԃ����������ɕ��ׂ�
			if (add->mSortOrder < task->mSortOrder)
			{
				mTaskList.insert(itr, add);
				return;
			}
		}
		itr++;
	}
	

	//�Ō�܂Œǉ�����ꏊ��������Ȃ������ꍇ�́A
	//���X�g�̍Ō���ɒǉ�����
	mTaskList.push_back(add);
}

//�^�X�N�����X�g�����菜��
void CTaskManager::Remove(CTask* remove, bool isSort)
{
	if (!isSort)
	{
		if (remove->mPrio == (int)CTaskPrio::Object)
		{
			mObjectList.remove(remove);
		}
	}

	mTaskList.remove(remove);
}

//�^�X�N���폜
void CTaskManager::Delete(CTask* del)
{
	//�폜����^�X�N
	if (del->mPrio == (int)CTaskPrio::Object)
	{
		mObjectList.remove(del);
	}

	//�폜���鎞�́A��Ƀ��X�g�����菜���Ă���폜����
	mTaskList.remove(del);
	delete del;
}

//���X�g���̃^�X�N�����ׂč폜
void CTaskManager::DeleteAll()
{
	//�S�č폜����̂ŁA�I�u�W�F�N�g���X�g�̒��g��S�ăN���A����
	mObjectList.clear();

	auto itr = mTaskList.begin();
	auto end = mTaskList.end();
	while (itr != end)
	{
		CTask* del = *itr;
		//���X�g�����菜���Ă���A�^�X�N���폜
		itr = mTaskList.erase(itr);
		delete del;
	}
}

//�^�X�N���̑S�^�X�N�̍X�V�������Ăяo��
void CTaskManager::Update()
{
	//�폜�t���O�������Ă���^�X�N���폜
	auto itr = mTaskList.begin();
	auto end = mTaskList.end();
	while (itr != end)
	{
		CTask* task = *itr;
		//�폜�t���O�������Ă�����폜
		if (task->mIsKill)
		{
			itr = mTaskList.erase(itr);
			delete task;
		}
		//�폜�t���O�������ĂȂ���΁A���̃^�X�N��
		else
		{
			itr++;
		}
	}

	//�S�Ẵ^�X�N���X�V
	itr = mTaskList.begin();
	end = mTaskList.end();
	while (itr != end)
	{
		CTask* task = *itr;
		if (task->mIsEnable)
		{
			task->Update();
		}
		itr++;
	}
}

//���X�g���̑S�̃^�X�N�̕`�揈�����Ăяo��
void CTaskManager::Render()
{
	//�I�u�W�F�N�g���X�g�̒��̃I�u�W�F�N�g��
	//���s�̍��W�ŕ��ёւ���
	mObjectList.sort
	(
		//�����_��
		[](const CTask* taskA, const CTask* taskB)
		{
			const ObjectBase* objA = dynamic_cast<const ObjectBase*>(taskA);
			const ObjectBase* objB = dynamic_cast<const ObjectBase*>(taskB);
			return objA->GetPos().y < objB->GetPos().y;
		}
	);
	
	//�I�u�W�F�N�g���X�g�̏��Ԃɏ������Ԃ̔ԍ���ݒ肷��
	int sortOrder = 0;
	for (auto& obj : mObjectList)
	{
		obj->SetSortOrder(sortOrder);
		sortOrder++;
	}

	auto itr = mTaskList.begin();
	auto end = mTaskList.end();
	while (itr != end)
	{
		CTask* task = *itr;
		//�^�X�N���L�����A�\������ݒ�ł���΁A
		//�`�揈�����Ăяo��
		if (task->mIsEnable && task->mIsShow)
		{
			task->Render();
		}
		itr++;
	}
}
