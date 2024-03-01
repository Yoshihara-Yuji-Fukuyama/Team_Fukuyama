#include "CEnemy2.h"
#include "CApplication.h"

#define TEXCOORD 168, 188, 190, 160 //�e�N�X�`���}�b�s���O
#define TEXCOORD2 136,156,190,160  //�E����2
#define TEXLEFT1 188,168,190,160 //�������P
#define TEXLEFT2 156,136,190,160 //�������Q
#define TEXCRY 196, 216, 190, 160  //�e�N�X�`���}�b�s���O




//�G�̐ݒ�
CEnemy2::CEnemy2(float x, float y, float w, float h, CTexture* pt)

{
	Set(x, y, w, h);

	Texture(pt, TEXCOORD);

	mTag = ETag::EENEMY;

	mVx = VELOCITY;

	sNum++;  //�G�̐����P���₷
}


//�G�̐����[���ɂ���
void CEnemy2::Enemy0()
{
	sNum = 0;
}


void CEnemy2::Update()
{
	switch (mState)
	{
	case EState::ECRY:

		//�����摜��ݒ�
		Texture(Texture(), TEXCRY);
		
		break;

	case EState::EMOVE:

		//X�����x���AX���W���X�V����
		X(X() + mVx);

		const int PITCH = 32;  //�摜��؂�ւ���Ԋu

		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mVx < 0.0f)
			{
				Texture(Texture(), TEXLEFT1);
			}

			else
			{
				Texture(Texture(), TEXCOORD);
			}

		}

		else
		{
			if (mVx < 0.0f)
			{
				Texture(Texture(), TEXLEFT2);
			}

			else
			{
				Texture(Texture(), TEXCOORD2);
			}
		}

		break;
	}	

	
}



void CEnemy2::Collision()
	{
			CApplication::TaskManager()->Collision(this);
    }



void CEnemy2::Collision(CCharacter* m, CCharacter* o)
{
	//�߂荞�ݒ����ϐ���錾����
	float x, y;

	switch (o->Tag())
	{
	case ETag::EPLAYER:

		if (CRectangle::Collision(o, &x, &y))
		{
			if (o->State() == EState::EJUMP && 
				mState != EState::ECRY)
			{

				sNum--; //�G�̐����P���炷

				mState = EState::ECRY;

			}
		}
		break;

	case ETag::ETURN:
		//�܂�Ԃ��ɓ��������Ƃ�
		if (CRectangle::Collision(o, &x, &y))
		{
			//�߂荞�܂Ȃ��ʒu�܂Ŗ߂�
			X(X() + x);

			Y(Y() + y);

			//X�����x�𔽓]������
			mVx = -mVx;

		}
		break;
	}
}





int CEnemy2::sNum = 0;

int CEnemy2::Num()
{
	return sNum;
}