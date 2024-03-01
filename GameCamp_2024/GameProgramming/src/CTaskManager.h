#pragma once

#include "CTask.h"
#include "CCharacter.h"

class CTaskManager
{
public:
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask* addTask);
	//���X�g����폜
	//Remove(�^�X�N�̃|�C���^)
	void Remove(CTask* addTask);
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
};
