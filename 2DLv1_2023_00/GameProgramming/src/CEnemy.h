#pragma once
#include "CCharacter.h"

class CEnemy :public CCharacter
{
public:
	void Update();

	bool Collision(CRectangle* rect);

	CEnemy(float x, float y, float w, float h,
		float l, float r, float b, float t, CTexture* pt);
	/*CEnemy(X���W, Y���W, ��, ����,
	�摜��,�摜�E,�摜��,�摜��,�e�N�X�`���̃|�C���^)*/

	void Collision();

	void Collision(CCharacter* m, CCharacter* o);
};