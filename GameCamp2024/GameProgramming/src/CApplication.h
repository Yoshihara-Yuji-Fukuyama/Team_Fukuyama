#pragma once
#include "CRectangle.h"
#include "CTexture.h"

class CApplication
{
public:
	//�ŏ��Ɉ�x�������s����v���O����
	void Start();
	//�J��Ԃ����s����v���O����
	void Update();

private:
	CRectangle mRectangle;
	CTexture mTexture;
};