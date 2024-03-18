#include <stdio.h>
#include "CUiFont.h"

#define FONT "Font.png"         //�t�H���g�̉摜
#define TIME_SIZE 1000,1000,20,20//���ԕ\���̃T�C�Y
#define SCORE_SIZE 520,1000,20,20//�X�R�A�\��


//�f�t�H���g�R���X�g���N�^
CUiFont::CUiFont()
	:mTime(0)
	, mScore(0)
{
	mFont.Load(FONT, 1, 64);
}

void CUiFont::SetTime(int time)
{
	mTime = time;
}

void CUiFont::SetScore(int score)
{
	mScore = score;
}

void CUiFont::Render()
{
	char str[16];

	//����
	sprintf(str, "TIME:%03d", mTime);
	mFont.Draw(TIME_SIZE, str);

	sprintf(str, "SCORE:%04d", mScore);
	mFont.Draw(SCORE_SIZE, str);
}
