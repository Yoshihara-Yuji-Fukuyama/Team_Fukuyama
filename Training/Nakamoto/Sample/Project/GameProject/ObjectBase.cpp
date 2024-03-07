#include "ObjectBase.h"

//�R���X�g���N�^
ObjectBase::ObjectBase(const CVector2D& pos)
	:CTask((int)CTaskPrio::Object)
	,mPos(pos)
{

}

//�f�X�g���N�^
ObjectBase::~ObjectBase()
{

}

//�I�u�W�F�N�g�̍��W��ݒ�
void ObjectBase::SetPos(const CVector2D& pos)
{
	mPos = pos;
}

//�I�u�W�F�N�g�̍��W���擾
const CVector2D& ObjectBase::GetPos()const
{
	return mPos;
}
