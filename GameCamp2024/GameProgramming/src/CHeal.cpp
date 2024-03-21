#include "CHeal.h"
#include "CPlayer.h"

#define HEAL_SIZE 100,100      //�傫��
#define HEAL_COLLIDER_SIZE 19,50 //����傫��
#define HEAL_SHADOW_SIZE 50,50   //�e�傫��
#define HEAL_SHADOW_POSY 60      //�e�̍���
#define TEX_HEAL 0,320,320,0 //�񕜃A�C�e���̃e�X�N�`���}�b�s���O
#define HEAL 0.2f            //�񕜊���
#define HEAL_BOTTOM 50      //�����v�Z�p

//static�ϐ��̒�`
CTexture CHeal::mTexture;

//static���\�b�h�̒�`
CTexture* CHeal::GetTexture()
{
	return &mTexture;
}

CHeal::CHeal()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, HEAL_COLLIDER_SIZE, CCollider::EColliderType::EITEM)
{

}

CHeal::CHeal(float x, float y, CTexture* texture)
	:CHeal()
{
	Set(x, y, HEAL_SIZE);

	Texture(texture, TEX_HEAL);

	mLeg = HEAL_BOTTOM;
	//�����ݒ�
	SetZ(GetY() - mLeg);
	//�񕜉e
	mShadow = HEAL_SHADOW_POSY;
	mpShadow = new CShadow(GetX(), GetShadowPosY(), HEAL_SHADOW_SIZE);
}

void CHeal::Update()
{
	//�������Ԃ�����
	SetSortOrder(GetY() - mLeg);
}

void CHeal::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::EPLAYER:	//�v���C���[�Ƃ̑̂̃R���C�_�Ƃ̏Փ˔���

		//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			CPlayer::GetInstance()->HealHp(HEAL);
			SetEnabled(false);
		}
		break;
	}
}

CHeal::~CHeal()
{
	mpShadow->SetEnabled(false);
}