#pragma once

#include "CTask.h"
#include "CCharacter.h"


class CTaskManager
{
public:

	/// <summary>
    /// �^�X�N�����X�g�ɒǉ�
    /// </summary>
    /// <param name="add">�ǉ�����^�X�N</param>
    /// <param name="isSort">�\�[�g���̌Ăяo�����ǂ���</param>
	void Add(CTask* addTask, bool isSort = false);
	/// <summary>
	/// �^�X�N�����X�g�����菜��
	/// </summary>
	/// <param name="remove">��菜���^�X�N�̃|�C���^�\</param>
	/// <param name="isSort">�\�[�g���̌Ăяo�����ǂ���</param>
	void Remove(CTask* removeTask, bool isSort = false);

	//�C���X�^���X�̎擾
	static CTaskManager* GetInstance();
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//�^�X�N�̍폜
	void Delete();
	//�^�X�N�̑S�폜
	void AllDelete();
	//�X�V
	void Update();
	//�`��
	void Render();
protected:
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
	CTask mHeadObj;//�I�u�W�F�̐擪�^�X�N
	CTask mTailObj;//�ŏI�^�X�N

	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
private:
	//�^�X�N�}�l�[�W���[�̃C���X�^���X
	static CTaskManager* mpInstance;
};
