#pragma once
#include "CCharacter.h"

class CBullet :public CCharacter
{
public:
	void Update();

	bool Collision(CRectangle* rect);

	CBullet();

	CBullet(float x, float y, float w, float h,
		float l, float r, float b, float t, CTexture* pt);
	/*CBullet(X���W, Y���W, ��, ����,
        �摜��,�摜�E,�摜��,�摜��,�e�N�X�`���̃|�C���^)*/

	//�Փˏ���2
	void Collision();

	//�Փˏ���4
	void Collision(CCharacter* m, CCharacter* o);
};