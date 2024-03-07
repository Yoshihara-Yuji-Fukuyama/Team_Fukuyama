#pragma once
#include "CTask.h"

//�Q�[�����̃I�u�W�F�N�g�̃x�[�X�N���X
class CObjectBase :public CTask
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�����ʒu</param>
	CObjectBase(const CVector2D& pos);

	//�f�X�g���N�^
	virtual ~CObjectBase();
	/// <summary>
	/// �I�u�W�F�N�g�̍��W��ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷����W</param>
	void SetPos(const CVector2D& pos);
	/// <summary>
	/// �I�u�W�F�N�g�̍��W���擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̍��W</returns>
	const CVector2D& GetPos() const;

protected:
	CVector2D mPos;//�I�u�W�F�N�g�̍��W
};
