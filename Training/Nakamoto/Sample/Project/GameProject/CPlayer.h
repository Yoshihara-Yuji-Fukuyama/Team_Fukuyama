#pragma once
#include "CharaBase.h"

class CPlayer : public CharaBase
{
//�A�N�Z�X�C���q
//�����ȊO�̊O������A�N�Z�X������
public:
	//�R���X�g���N�^
	CPlayer();
	//�f�X�g���N�^
	~CPlayer();

	//���S�����Ƃ��̏���
	void Death() override;

	//�X�V����
	void Update() override;
	//�`�揈��
	void Render() override;

//�������g�̃N���X�����A�N�Z�X�ł��Ȃ�
//�����o�ϐ��͊�{private
private:
	TexAnimData* mpAnimData;	//�A�j���[�V�����̃f�[�^
	CImage* mpImage;	//�v���C���[�̉摜

//�����Ǝ��N���X���p�������N���X�ŃA�N�Z�X�ł���
protected:

};