#pragma once
#include "CCharacter.h"
#include "CInput.h"
#include "CSound.h"

class CPlayer2 :public CCharacter
{
public:
	//CPlayer2(X���W,Y���W,��,����,�e�N�X�`���̃|�C���^)
	CPlayer2(float x, float y, float w, float h, CTexture* pt);

	//�X�V����
	void Update();

	//�Փˏ����Q
	void Collision();

	//�Փˏ����S
	void Collision(CCharacter* m, CCharacter* o);

	//HP���擾
	static int Hp();

private:
	CInput mInput;

	static int sHp; //HP

	int mInvincible; //���G�J�E���^

	CSound mSoundJump; //�W�����vSE
};