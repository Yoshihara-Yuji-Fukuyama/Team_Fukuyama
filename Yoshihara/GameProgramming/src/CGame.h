#pragma once
#include "CEnemy.h"
#include "CBackground.h"
#include "CPlayer.h"

/*
CGame�N���X
�Q�[���N���X
�Q�[���̃}�b�v���쐬���A
�L�����N�^��z�u����
*/

class CGame
{
public:
	//�X�V
	void Update();
	//��������
	void Start();

	//�f�t�H���g�R���X�g���N�^
	CGame();
	//�f�X�g���N�^
	~CGame();

	//�G����
	void CreateEnemy();

private:
	void SetCamera();//�J������ݒ�

	int mFrame;//�t���[���J�E���^
};
