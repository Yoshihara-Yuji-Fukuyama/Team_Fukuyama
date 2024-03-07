#include "CTask.h"
#include "CTaskManager.h"

//�R���X�g���N�^
CTask::CTask(int priority)
	:mPriority(priority)
	, mSortOrder(0)
	, mIsEnable(true)
	, mIsShow(true)
	, mIsKill(false)
{
	//�^�X�N�̐����Ɠ�����CCTaskManager�̃��X�g�Ɏ��M��ǉ�
	CTaskManager::Add(this);
}

//�f�X�g���N�^
CTask::~CTask()
{
	//�^�X�N�̍폜�Ɠ�����CTaskManager�̃��X�g���玩�M����菜��
	CTaskManager::Remove(this);
}

//�D��x��ݒ�
void CTask::SetPriority(int priority)
{
	mPriority = priority;
	//1��^�X�N�̃��X�g���玩�M����菜���A
	//���̌����1�x�^�X�N�̃��X�g�ɒǉ�����֐����Ăт������Ƃ�
	//�V�����D��x�̏ꏊ�Ƀ^�X�N��ύX����
	CTaskManager::Remove(this,true);
	CTaskManager::Add(this,true);
}

//�D��x���擾
int CTask::GetPriority() const
{
	return mPriority;
}

//�������Ԃ�ݒ�
void CTask::SetSortOrder(int order)
{
	//�������Ԃ�ύX��Ƀ��X�g���̕��ёւ����s��
	mSortOrder = order;
	CTaskManager::Remove(this, true);
	CTaskManager::Add(this, true);
}

//�������Ԃ��擾
int CTask::GetSortOrder() const
{
	return mSortOrder;
}

//�L�����ǂ�����ݒ�
void CTask::SetEnable(bool enable)
{
	mIsEnable = enable;
}

//�L�����ǂ����擾
bool CTask::IsEnable() const
{
	return mIsEnable;
}

//�\�����邩�ǂ�����ݒ�
void CTask::SetShow(bool show)
{
	mIsShow = show;
}

//�\�����邩�ǂ������擾
bool CTask::IsShow() const
{
	return mIsShow;
}

//�^�X�N���폜
void CTask::Kill()
{
	mIsKill = true;
}

//�^�X�N�̍폜�t���O�������Ă��邩
bool CTask::IsKill() const
{
	return mIsKill;
}

void CTask::Update()
{

}

void CTask::Render()
{

}
