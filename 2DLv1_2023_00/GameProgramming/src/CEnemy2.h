#pragma once
#include "CCharacter.h"

class CEnemy2 :public CCharacter
{
public:

	//�Փˏ����Q
	void Collision();

	//�Փˏ����S
	void Collision(CCharacter* m, CCharacter* o);

	//CEnemy2(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CEnemy2(float x, float y, float w, float h, CTexture* pt);

	void Enemy0();

	//�X�V����
	void Update();

	//�G�̐����擾
	static int Num();


private:

	static int sNum; //�G�̐�

};