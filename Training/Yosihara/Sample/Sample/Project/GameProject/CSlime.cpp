#include "CSlime.h"

//�R���X�g���N�^
CSlime::CSlime(int type, const CVector2D& pos)
	: CCharacterBase(pos,50)
	, mpAnimData(nullptr)
	, mpImage(nullptr)
	, mType(type)
{

	//�A�j���[�V�����f�[�^�𐶐�
	int frame = 4;
	mpAnimData = new TexAnimData[1]
	{
		{
			new TexAnim[4]
			{
				{ 0, frame}, { 1, frame},
		        { 2, frame}, { 3, frame},
			},
			4
		},
	};
	//�摜��ǂݍ���
	std::string ImagePath;
	if (mType == 0) ImagePath = "slime_a.png";
	else if (mType == 1) ImagePath = "slime_b.png";
	else if (mType == 2)ImagePath = "slime_c.png";
	mpImage = CImage::CreateImage
	(
		ImagePath.c_str(),//�摜�t�@�C���̃p�X
		mpAnimData,//�A�j���[�V�����̃f�[�^
		256.0f, 256.0f//1�R�}�̕��ƍ���
	);
	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(128.0f, 184.0f);
	mpImage->SetFlipH(true);
}

//�f�X�g���N�^
CSlime::~CSlime()
{
	//�A�j���[�V�����̃f�[�^�̔z����폜
	for (int i = 0; i < 1; i++)
	{
		delete[] mpAnimData[i].pData;
	}
	delete[] mpAnimData;
	//�摜�f�[�^���폜
	delete[] mpImage;
}


//�X�V����
void CSlime::Update()
{
	//�C���[�W�ɍ��W��ݒ肵�āA�A�j���[�V�������X�V
	mpImage->SetPos(mPos);
	mpImage->UpdateAnimation();
}

//�`�揈��
void CSlime::Render()
{
	mpImage->Draw();
}