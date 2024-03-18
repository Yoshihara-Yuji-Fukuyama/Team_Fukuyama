#pragma once
#include "CFont.h"

class CUiFont
{
public:
	//�f�t�H���g�R���X�g���N�^
	CUiFont();

	//����
	void SetTime();

	//���Ԃ̎擾
	int GetTime();

	//�X�R�A
	void SetScore(int score);

	//�����̕`��
	void Render();

	//static���\�b�h�̐錾
	static CUiFont* GetInstance();

private:
	int mTime;//�^�C�����~�b�g

	int mScore;//���_

	CFont mFont;

	//static�ϐ��̐錾
	static CUiFont* mpInstance;

};