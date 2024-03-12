#include "CPlayer.h"
#include "CApplication.h"

#define PLAYER_STARTSET 100.0f,300.0f,300.0f,300.0f//x,y,w,h �v���C���[�̏����ʒu
#define PLAYER_TEXCOORD 0 ,600 ,3000 ,2400	//�v���C���[�e�N�X�`���}�b�s���O
#define VELOCITY_PLAYER 3.0f	            //�v���C���[�̈ړ����x
#define JUMPV0 (30 / 1.4f)		            //�W�����v�̏����x
#define GRAVITY (30 / 30)		            //�d�͉����x
#define PLAYER_BOTTOM 270                   //�v���C���[�����v�Z�p

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
		mpInstance= new CPlayer(PLAYER_STARTSET);
	}
	return mpInstance;
}

CPlayer::CPlayer()
	:CCharacter((int)CTaskPriority::Object)
	, mJump(0)
{
	mpInstance = this;
	mState = EState::EMOVE;
}

CPlayer::CPlayer(float x, float y, float w, float h)
	: CPlayer()
{
	Set(x, y, w, h);

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
		//�W�����v�J�n���̍��W
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
		//�X�e�[�^�X���ړ��������̍��W��250�����̎�
		if (mState == EState::EMOVE && GetY() - PLAYER_BOTTOM < 250)
		{
			SetY(GetY() + VELOCITY_PLAYER);
		}
		//�X�e�[�^�X���W�����v���W�����v�J�n���̍��W��250�ȉ��̎�
		if (mState == EState::EJUMP && mJump < 250)
		{
			//�W�����v�������Z
			mJump += VELOCITY_PLAYER;
			SetY(GetY() + VELOCITY_PLAYER);
		}
	}
	//���Ɉړ�
	if (mInput.Key('S'))
	{
		//�X�e�[�^�X���ړ��������̍��W��0���傫����
		if (mState == EState::EMOVE && GetY() - PLAYER_BOTTOM > 0)
		{
			SetY(GetY() - VELOCITY_PLAYER);
		}
		//�X�e�[�^�X���W�����v���W�����v�J�n���̍��W��0���傫����
		if (mState == EState::EJUMP && mJump > 0)
		{
			//�W�����v�������Z
			mJump -= VELOCITY_PLAYER;
			SetY(GetY() - VELOCITY_PLAYER);
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
		//�W�����v���ɉ�ʉ���艺�ɍs���Ȃ��悤�ɂ���
		if (GetY() - PLAYER_BOTTOM < 0)
		{
			//��Ԃ��ړ��ɕύX
			mState = EState::EMOVE;
		}
	}
}

//���S����
void CPlayer::Death()
{
	//�^�X�N���X�g����폜
	SetEnabled(false);
}
