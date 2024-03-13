#include "CPlayer.h"
#include "CApplication.h"

#define PLAYER_TEXTURE "Player.png"     //�v���C���[�摜
#define PLAYER_TEXCOORD 0 ,600 ,3000 ,2400	//�v���C���[�e�N�X�`���}�b�s���O

#define PLAYER_STARTSET 100.0f,300.0f,300.0f,300.0f//x,y,w,h �v���C���[�̏����ʒu


#define VELOCITY_PLAYER 3.0f	//�v���C���[�̈ړ����x
#define JUMPV0 (30 / 1.4f)		//�W�����v�̏����x
#define GRAVITY (30 / 30)		//�d�͉����x

//static�ϐ��̒�`
CTexture CPlayer::mTexture;

CPlayer* CPlayer::mpInstance;

//���\�b�h�̒�`
CTexture* CPlayer::GetTexture()
{
	return &mTexture;
}

//�C���X�^���X�̎擾
CPlayer* CPlayer::GetInstance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CPlayer(PLAYER_STARTSET);
	}
	return mpInstance;
}

CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, 100, 100)
	,mJump(0)
{
	mpInstance = this;
	mState = EState::EMOVE;
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
		//��̈ړ�����
		if (GetY() - GetH() < 250)
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
		//���̈ړ�����
		if (GetY() - GetH() > 0)
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
			mJump = (GetY() - GetH());
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
		if (GetY() - GetH() < mJump)
		{
			//��Ԃ��ړ��ɕύX
			mState = EState::EMOVE;
		}
		//�W�����v���ɉ�ʉ���艺�ɍs���Ȃ��悤�ɂ���
		else if (GetY() - GetH() <= 0)
		{
			//��Ԃ��ړ��ɕύX
			mState = EState::EMOVE;
		}

	}
}
