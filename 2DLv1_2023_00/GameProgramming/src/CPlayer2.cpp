#include "CPlayer2.h"
#include "CApplication.h"

#define TEXCOORD 168,188,158,128//�e�N�X�`���}�b�s���O
#define TEXCOORD2 136,156,158,128  //�E����2
#define TEXLEFT1 188,168,158,128 //�������P
#define TEXLEFT2 156,136,158,128 //�������Q
#define VELOCITY 4.0f //�ړ����x
#define GRAVITY (TIPSIZE / 20.0f) //�d�͉����x
#define JUMPV0 (TIPSIZE / 1.4f) //�W�����v�̏���
#define  TEXCRY 196,216,158,128 //�e�N�X�`���}�b�s���O
#define HP 3 //HP�̏����l�͂R
#define SE_JUMP "res\\jump.wav" //�W�����v�̉����t�@�C��

//�v���C���[�̐ݒ�
CPlayer2::CPlayer2(float x, float y, float w, float h, CTexture* pt)
	:mInvincible(0)
{
	Set(x, y, w, h);

	Texture(pt, TEXCOORD);

	mTag = ETag::EPLAYER;

	sHp = HP;

	mSoundJump.Load(SE_JUMP); //�W�����v�����[�h

}



void CPlayer2::Update()
{

	//���G���Ԓ��̓J�E���g���������A����
	if (mInvincible > 0)
	{
		//�P���Z����
		mInvincible--;

		//����
		mState = EState::ECRY;

	}




	//J�L�[�ŃW�����v
	if (mState != EState::EJUMP&&mInput.Key('J'))
	{
		mVy = JUMPV0;

		mState = EState::EJUMP;

		//�W�����v��
		mSoundJump.Play();
	}



	//A�L�[�ō���4�ړ�
	if (mInput.Key('A'))
	{
		mVx = -VELOCITY;

		X(X() + mVx);
	}



	//D�L�[�ŉE��4�ړ�
	if (mInput.Key('D'))
	{
		mVx = VELOCITY;

		X(X() + mVx);
	}



	//Y���W��Y�����x��������
	Y(Y() + mVy);

	mVy -= GRAVITY;



	//�X�e�[�^�X��ECRY�Ȃ狃��
	if (mState == EState::ECRY)
	{
		//�����摜��ݒ�
		Texture(Texture(), TEXCRY);
	}


	else
	{

		const int PITCH = 32;  //�摜��؂�ւ���Ԋu
		

		if ((int)X() % PITCH < PITCH / 2)
		{
			if (mVx < 0.0f)//���ֈړ�
			{
				//�������P��ݒ�
				Texture(Texture(), TEXLEFT1);
			}

			else
			{
				//�ʏ�̉摜��ݒ�
				Texture(Texture(), TEXCOORD);
			}

		}


		else
		{
			if (mVx < 0.0f) //���ֈړ�
			{
				//�������Q��ݒ�
				Texture(Texture(), TEXLEFT2);
			}

			else
			{
			    //2�Ԗڂ̉摜��ݒ�
			    Texture(Texture(), TEXCOORD2);
			}

		}

	}

}



void CPlayer2::Collision()
{
	CApplication::TaskManager()->Collision(this);
}



void CPlayer2::Collision(CCharacter* m, CCharacter* o)
{
	float x, y;
	
	switch (o->Tag())
	{
	case ETag::EENEMY:
		if (CRectangle::Collision(o, &x, &y))
		{
			//�G�̏Փ˔�������s
			o->Collision(o, m);

			X(X() + x); //�߂荞�܂Ȃ�

			Y(Y() + y); //�߂荞�܂Ȃ�

			//���n��������
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;

				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}


				else
				{
					//���G���Ԃł͂Ȃ����G�������Ă��Ȃ�
					if (mInvincible == 0 && o->State() != EState::ECRY)
					{
						//�W�����v�łȂ���΋���
						mState = EState::ECRY;

						mInvincible = 60;

						sHp--;
					}
				}
			}


			else
			{
				//���G���Ԃł͂Ȃ����G�������Ă��Ȃ�
				if (mInvincible == 0 && o->State() != EState::ECRY)
				{
					//�W�����v�łȂ���΋���
					mState = EState::ECRY;

					mInvincible = 60;

					sHp--;
				}
			}

		}
		break;


	case ETag::EPLAYER:

		break;


	case ETag::EBLOCK:
		if (CRectangle::Collision(o, &x, &y))
		{
			X(X() + x);
			Y(Y() + y);

			//���n�����Ƃ�
			if (y != 0.0f)
			{
				//Y�����x��0�ɂ���
				mVy = 0.0f;

				if (y > 0.0f)
				{
					mState = EState::EMOVE;
				}
			}

		}
		break;
	}

}



int CPlayer2::sHp = 0; //HP


int CPlayer2::Hp()
{
	return sHp;
}