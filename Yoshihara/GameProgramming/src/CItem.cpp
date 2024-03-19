#include "CItem.h"

#define TEX_HEAL 0,320,320,0

//static�ϐ��̒�`
CTexture CItem::mTexture;

//static���\�b�h�̒�`
CTexture* CItem::GetTexture()
{
	return &mTexture;
}

CItem::CItem()
	:CCharacter((int)CTaskPriority::Object)
	, mCollider(this, &mX, &mY, &mZ, 10, 10, CCollider::EColliderType::EITEM)
{

}

CItem::CItem(float x, float y, float w, float h, CTexture* texture)
{
	Set(x, y, w, h);

	Texture(texture, TEX_HEAL);

}

void CItem::Collision(CCollider* m, CCollider* o)
{
	float ax, ay;

	switch (o->GetCType())
	{
	case CCollider::EColliderType::EPLAYER:	//�X���C���̑̂̃R���C�_�Ƃ̏Փ˔���

		//�R���C�_��m��o���Փ˂��Ă��邩���肵�Ă��邩����
		if (CCollider::Collision(m, o, &ax, &ay))
		{
			//�v���C���[�Ƃ̏Փ˔�������s(�߂荞�܂Ȃ�����)
			//SetX(GetX() + ax);
			//������
			//SetY(GetY() + ay);


		}
		break;
	}
}