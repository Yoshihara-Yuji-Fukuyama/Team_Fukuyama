#pragma once
#include "CTaskManager.h"

class CCollisionManager :public CTaskManager
{
public:
	//�Փˏ���
	void Collision();

	//�C���X�^���X�̎擾
	static CCollisionManager* GetInstance();
private:
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};