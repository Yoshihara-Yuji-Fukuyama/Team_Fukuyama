#pragma once
#include "CFont.h"

/*
CUi
���[�U�[�C���^�[�t�F�[�X�N���X
*/

class CUi
{
public:
	CUi();
	
	void Time(int time); //Time(����)

	void Hp(int hp); //HP

	void Enemy(int enemy);	//Enemy(�G�̐�)

	void Render();

	void Start(); //�X�^�[�g���

	void Over(); //�Q�[���I�[�o�[�\��

	void Clear(); //�Q�[���N���A�\��

private:
	int mTime;  //�o�ߎ���

	int mHp; //HP

	int mEnemy; //�G�̐�

	CFont mFont;
};