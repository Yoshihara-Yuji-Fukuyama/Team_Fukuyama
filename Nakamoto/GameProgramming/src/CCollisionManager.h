#pragma once

#include "CTaskManager.h"

class CCollisionManager : public CTaskManager
{
public:
	//�Փˏ���
	void Collision();
	//�C���X�^���X�̎擾
	static CCollisionManager* Instance();
private:
	//�R���C�_�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};
