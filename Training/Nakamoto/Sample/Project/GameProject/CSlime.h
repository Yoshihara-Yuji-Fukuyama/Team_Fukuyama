#pragma once
#include "CharaBase.h"

class CSlime :public CharaBase
{
	//�A�N�Z�X�C���q
//�����ȊO�̊O������A�N�Z�X������
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="type">�X���C���̎��</param>
	/// <param name="pos">�����ʒu</param>
	CSlime(int type ,const CVector2D &pos);
	//�f�X�g���N�^
	~CSlime() ;

	//�X�V����
	void Update() override;
	//�`�揈��
	void Render() override;

	//�������g�̃N���X�����A�N�Z�X�ł��Ȃ�
	//�����o�ϐ��͊�{private
private:
	TexAnimData* mpAnimData;	//�A�j���[�V�����̃f�[�^
	CImage* mpImage;	//�摜
	int mType;			//�X���C���̎��

};