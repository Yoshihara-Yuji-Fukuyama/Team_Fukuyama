#include "CPlayer.h"
#include "CApplication.h"

#define PLAYER_TEXTURE "Player.png"         //�v���C���[�摜
#define PLAYER_TEXCOORD 0 ,600 ,3000 ,2400	//�v���C���[�e�N�X�`���}�b�s���O
#define VELOCITY_PLAYER 3.0f	            //�v���C���[�̈ړ����x
#define JUMPV0 (30 / 1.4f)		            //�W�����v�̏����x
#define GRAVITY (30 / 30)		            //�d�͉����x
#define PLAYER_BOTTOM 270                   //�v���C���[�����v�Z�p

//static�ϐ��̒�`
CTexture CPlayer::mTexture;

//���\�b�h�̒�`
CTexture* CPlayer::GetTexture()
{
	return &mTexture;
}

CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
{
	
}

CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);

	GetTexture()->Load(PLAYER_TEXTURE);

	Texture(GetTexture(), PLAYER_TEXCOORD);
}

CPlayer::~CPlayer()
{

}

void CPlayer::Update()
{
	//��Ԃ��W�����v����Ȃ��Ȃ珈�����Ԃ��X�V
	if (mState == EState::EJUMP)
	{
		SetSortOrder(mJump);
	}
	else
	{
		SetSortOrder(GetY() - PLAYER_BOTTOM);
	}
	//���Ɉړ�
	if (mInput.Key('A'))
	{
		SetX(GetX() - VELOCITY_PLAYER);
	}
	//�E�Ɉړ�
	if (mInput.Key('D'))
	{
		SetX(GetX() + VELOCITY_PLAYER);
	}
	//��Ɉړ�
	if (mInput.Key('W'))
	{
		if (GetY() - PLAYER_BOTTOM < 500)
		{
			SetY(GetY() + VELOCITY_PLAYER);
			if (mState == EState::EJUMP)
			{
				//�W�����v�������Z
				mJump += VELOCITY_PLAYER;
			}
		}
	}
	//���Ɉړ�
	if (mInput.Key('S'))
	{
		if (GetY() - PLAYER_BOTTOM > 0)
		{
			SetY(GetY() - VELOCITY_PLAYER);
			if (mState == EState::EJUMP)
			{
				//�W�����v�������Z
				mJump -= VELOCITY_PLAYER;
			}
		}
	}
	//�W�����v
	if (mInput.Key(VK_SPACE))
	{
		if (mState != EState::EJUMP)
		{
			//�W�����v�̊J�n����Y���W���擾
			mJump = (GetY() - PLAYER_BOTTOM);
			//�W�����v�̏����x��ݒ�
			mVy = JUMPV0;
			//��Ԃ��W�����v�ɕύX
			mState = EState::EJUMP;
		}
	}
	//�W�����v����
	if (mState == EState::EJUMP)
	{
		//Y���W��Y�����x��������
		SetY(GetY() + mVy);
		//Y�����x�ɏd�͂����Z����
		mVy -= GRAVITY;

		//�W�����v�����ȉ���Y���W���Ȃ�����
		if (GetY() - PLAYER_BOTTOM < mJump)
		{
			//��Ԃ��ړ��ɕύX
			mState = EState::EMOVE;
		}

		if (GetY() - PLAYER_BOTTOM < 0)
		{
			//��Ԃ��ړ��ɕύX
			mState = EState::EMOVE;
		}
	}
}

void CPlayer::Death()
{
	//�^�X�N���X�g����폜
	SetEnabled(false);
}