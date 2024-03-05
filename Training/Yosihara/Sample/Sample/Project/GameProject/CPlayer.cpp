#include "CPlayer.h"

//�R���X�g���N�^
CPlayer::CPlayer()
	:mPos(CVector2D(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f))
	, mpAnimData(nullptr)
	, mpImage(nullptr)
	, mHp(100)
{

	//�v���C���[�̃A�j���[�V�����f�[�^�𐶐�
	int frame = 6;
	mpAnimData = new TexAnimData[2]
	{
		//�ҋ@�A�j���[�V����
		{
			new TexAnim[6]
			{
			{0,frame},{1,frame},{2,frame},
			{3,frame},{4,frame},{5,frame},
			},
			6
		},
		//�ړ��A�j���[�V����
		{
			 new TexAnim[6]
		    {
			    {6,frame},{7,frame},{8,frame},
		        {9,frame},{10,frame},{11,frame},

            },
			6
        },

	};
	//�v���C���[�̉摜��ǂݍ���
	mpImage = CImage::CreateImage
	(
		"player.png",//�摜�t�@�C���̃p�X
		mpAnimData,//�A�j���[�V�����̃f�[�^
		384.0f,384.0f//1�R�}�̕��ƍ���
	);
	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(192.0f, 328.0f);
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{
	//�A�j���[�V�����̃f�[�^�̔z����폜
	for (int i = 0; i < 2; i++)
	{
		delete[] mpAnimData[i].pData;
	}
	delete[] mpAnimData;
	//�摜�f�[�^���폜
	delete[] mpImage;
}

//�v���C���[�̍��W���擾
const CVector2D& CPlayer::GetPos() const
{
	return mPos;
}

//�v���C���[�̍��W��ݒ�
void CPlayer::SetPos(const CVector2D& pos)
{
	mPos = pos;
}

//�X�V����
void CPlayer::Update()
{
	bool isMove = false;
	//���L�[�������Ă����
	if (HOLD(CInput::eLeft))
	{
		//�������ֈړ�
		mPos.x -= 5.0f;
		mpImage->ChangeAnimation(1);
		mpImage->SetFlipH(true);
		isMove = true;
	}
	//�E�L�[�������Ă����
	else if (HOLD(CInput::eRight))
	{
		//�E�����ֈړ�
		mPos.x += 5.0f;
		mpImage->ChangeAnimation(1);
		mpImage->SetFlipH(false);
		isMove = true;
	}
	//��L�[�������Ă����
	if (HOLD(CInput::eUp))
	{
		//������ֈړ�
		mPos.y -= 3.0f;
		mpImage->ChangeAnimation(1);
		isMove = true;

	}
	//���L�[�������Ă����
	else if (HOLD(CInput::eDown))
	{
		//�������ֈړ�
		mPos.y += 3.0f;
		mpImage->ChangeAnimation(1);
		isMove = true;
	}
	//������Ă��Ȃ��ꍇ
	if(!isMove)
	{
		mpImage->ChangeAnimation(0);
	}
	//�C���[�W�ɍ��W��ݒ肵�āA�A�j���[�V�������X�V
	mpImage->SetPos(mPos);
	mpImage->UpdateAnimation();
}

//�`�揈��
void CPlayer::Render()
{
	mpImage->Draw();
}