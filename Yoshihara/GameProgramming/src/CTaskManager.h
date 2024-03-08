#pragma once

#include "CTask.h"
#include "CCharacter.h"

class CTaskManager
{
public:
	//�C���X�^���X�̎擾
	static CTaskManager* GetInstance();
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	void Add(CTask* addTask);
	//���X�g����폜
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
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
private:
	//�^�X�N�}�l�[�W���[�̃C���X�^���X
	static CTaskManager* mpInstance;
};
