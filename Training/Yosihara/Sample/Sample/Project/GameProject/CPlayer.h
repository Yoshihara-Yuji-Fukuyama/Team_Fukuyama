#pragma once
#include "CCharacterBase.h"

class CPlayer :public CCharacterBase
{
//�A�N�Z�X�C���q
//�����ȊO�̊O������A�N�Z�X������
public:
	//�R���X�g���N�^
	CPlayer();
	//�f�X�g���N�^
	~CPlayer();

	//���S�������̏���
	void Death() override;

	//�X�V����
	void Update() override;
	//�`�揈��
	void Render() override;

//�������g�̃N���X�����A�N�Z�X�ł��Ȃ�
//�����o�ϐ��͊�{private
private:
	TexAnimData* mpAnimData;//�A�j���[�V�����̃f�[�^
	CImage* mpImage;//�v���C���[�̉摜

};
