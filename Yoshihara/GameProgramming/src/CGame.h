#pragma once
#include "CEnemy.h"
#include "CBackground.h"
#include "CPlayer.h"
#include "CUiFont.h"
#include "CUiTexture.h"
#include "CShadow.h"
#include "CInput.h"
#include "CTitle.h"
#include "CHeal.h"
#include <time.h>

/*
CGame�N���X
�Q�[���N���X
�Q�[���̃}�b�v���쐬���A
�L�����N�^��z�u����
*/

class CGame
{
public:
	enum class EGameScene
	{
		GameTitle,
		GameStart,
		Game,
		GameResult,
		GameEnd,
	};
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
	CInput mInput;

	void SetCamera();//�J������ݒ�

	clock_t start;//�Q�[���n�܂�̎��Ԃ�ۑ�

	int mFrame;//�t���[���J�E���^

	double mCount;//�b���J�E���^

	bool isTitleCreate;//�^�C�g���𐶐����Ă��邩

	bool isStartTime;//�n�܂�̎��Ԃ�ۑ����Ă��邩

	bool isEnter;//�G���^�[�������ė����܂ł��Z�b�g��

	EGameScene mScene;//�Q�[���̃V�[��
};
