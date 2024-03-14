#include "CFont.h"

//�e�N�X�`�������[�h
void CFont::Load(const char* file, int row, int col)
{
	//�e�N�X�`�������[�h
	mTexture.Load(file);
	//�s�Ɨ��ݒ�
	mTexture.SetRowCol(row, col);
}

//������`��
void CFont::Draw(float x, float y, float w, float h, char c)
{
	int i = c - 0x20;
	mTexture.DrawImage(x - w, x + w, y - h, y + h, i);
}

//�������`��
void CFont::Draw(float x, float y, float w, float h, char c[])
{
	//c[i]�̒��g��\0�ł͂Ȃ��Ȃ瑱����
	for (int i = 0; c[i] != '\0'; i++)
	{
		Draw(x, y, w, h, c[i]);
		x += w * 2;
	}
	return;
}