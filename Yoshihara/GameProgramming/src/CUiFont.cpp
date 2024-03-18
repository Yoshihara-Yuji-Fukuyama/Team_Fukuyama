#include <stdio.h>
#include "CUiFont.h"

#define FONT "Font.png"         //�t�H���g�̉摜
#define TIME_SIZE 800,1010,20,20//���ԕ\���̃T�C�Y
#define SCORE_SIZE 220,1010,20,20//�X�R�A�\��

#define TIME_MAX 189 //�ő厞��

//static�ϐ��̐錾
CUiFont* CUiFont::mpInstance;

//static���\�b�h�̐錾
CUiFont* CUiFont::GetInstance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CUiFont();
	}
	return mpInstance;
}


//�f�t�H���g�R���X�g���N�^
CUiFont::CUiFont()
	:mTime(TIME_MAX)
	, mScore(0)
{
	mFont.Load(FONT, 1, 64);
}

void CUiFont::SetTime()
{
	mTime = mTime--;
}

int CUiFont::GetTime()
{
	return mTime;
}

void CUiFont::SetScore(int score)
{
	mScore = mScore + score;
}

void CUiFont::Render()
{
	char str[16];

	//����
	sprintf(str, "TIME:%03d", mTime);
	mFont.Draw(TIME_SIZE, str);

	sprintf(str, "SCORE:%06d", mScore);
	mFont.Draw(SCORE_SIZE, str);
}
