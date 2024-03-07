#include "CObjectBase.h"

//�R���X�g���N�^
CObjectBase::CObjectBase(const CVector2D& pos)
	:CTask((int)CTaskPriority::Object)
	,mPos(pos)
	
{

}

//�f�X�g���N�^
CObjectBase::~CObjectBase()
{

}

//�I�u�W�F�N�g�̍��W��ݒ�
void CObjectBase::SetPos(const CVector2D& pos)
{
	mPos = pos;
}

//�I�u�W�F�N�g�̍��W���擾
const CVector2D& CObjectBase::GetPos() const
{
	return mPos;
}

