#pragma once
#include "CTask.h"

//���ׂẴI�u�W�F�N�g�̉e��`�悷��
class CShadowManager :public CTask
{
public:
	//�R���X�g���N�^
	CShadowManager();
	//�f�X�g���N�^
	~CShadowManager();

	//�X�V
	void Update() override;
	//�`��
	void Render() override;
private:
	CImage* mpImage;//�e�̉摜�f�[�^
};