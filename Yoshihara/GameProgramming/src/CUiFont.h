#pragma once
#include "CFont.h"

class CUiFont
{
public:
	//�f�t�H���g�R���X�g���N�^
	CUiFont();

	//�c�莞��
	void SetTime(int time);

	//�X�R�A
	void SetScore(int score);

	//�����̕`��
	void Render();


private:
	int mTime;//�^�C�����~�b�g

	int mScore;//���_

	CFont mFont;


};