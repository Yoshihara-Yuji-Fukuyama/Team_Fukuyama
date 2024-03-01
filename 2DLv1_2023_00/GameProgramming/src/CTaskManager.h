#ifndef CTaskManager_H
#define CTaskManager_H
//�^�X�N�N���X�̃C���N���[�h
#include "CTask.h"
#include "CCharacter.h"

/*
�^�X�N�}�l�[�W��
�^�X�N���X�g�̊Ǘ�
*/
class CTaskManager {
public:
	//�f�X�g���N�^
	virtual ~CTaskManager();
	//���X�g�ɒǉ�
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask* addTask);
	//���X�g����폜
	//Remove(�^�X�N�̃|�C���^)
	void Remove(CTask* task);
	//�^�X�N�̍폜
	void Delete();
	//�^�X�N�̑S�폜
	void AllDelete();
	//�Փˏ���1
	void Collision();
	//�Փˏ���3
	//Collision(�Փˌ��̃|�C���^)
	void Collision(CCharacter* character);
	//�X�V
	void Update();
	//�`��
	void Render();
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
protected:
	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N
};
#endif