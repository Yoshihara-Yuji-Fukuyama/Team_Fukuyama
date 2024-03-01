#pragma once
#include "CUi.h"
#include "CEnemy2.h"
#include"CPlayer2.h"

//�萔�̒�`
#define TEXTURE "image.png" //�e�N�X�`���̃t�@�C����
#define TIPSIZE 20.0f //�}�b�v�v�f�̃T�C�Y

/*
CGame�N���X
�Q�[���N���X
�Q�[���̃}�b�v���쐬���A
�L�����N�^��z�u����
*/

class CGame
{
public:
	CGame(); //�f�t�H���g�R���X�g���N�^(��������)

	void Update(); //�X�V����

	void Start(); //�X�^�[�g����

	//�Q�[���I�[�o�[����
	//true:�Q�[���I�[�o�[
	bool IsOver();

	//�Q�[���I�[�o�[����
	void Over();

	//�Q�[���N���A����
	//true:�Q�[���N���A
	bool IsClear();

	//�Q�[���N���A����
	void Clear();

	//�f�X�g���N�^
	~CGame();

private:
	CUi* mpUi; //UI�N���X�̃|�C���^

	CEnemy2* mpEnemy2;

	int mTime; //�o�ߎ���

	int mCdx, mCdy; //�J�����ƃv���C���[�̍��W�̍���

	CPlayer2* mpPlayer; //�v���C���[�̃|�C���^

	void CameraSet(); //�J�����ݒ�

};
