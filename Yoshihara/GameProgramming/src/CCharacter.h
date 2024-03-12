#pragma once
#include "CTexture.h"
#include "CRectangle.h"
#include "CTask.h"

//�R���C�_�N���X�̐錾
class CCollider;

class CCharacter :public CRectangle,public CTask//�e�N���X��
{
public:
	enum class EState//���
	{
		EWAIT,    //�ҋ@
		EMOVE,    //�ړ�
		EJUMP,    //�W�����v
	};
	//�f�t�H���g�R���X�g���N�^
	CCharacter();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="priority">�D��x</param>
	CCharacter(int priority);

	//�f�X�g���N�^
	virtual ~CCharacter();

	//mpTexture��Ԃ�
	CTexture* GetTexture();

	/// <summary>
	/// �L���t���O��ݒ�
	/// </summary>
	/// <param name="isEnabled"></param>
	void SetEnabled(bool isEnabled);

	//�L���t���O��Ԃ�
	bool GetEnabled();

	/// <summary>
	/// �������Ԃ�ݒ�
	/// </summary>
	/// <param name="order">��������</param>
	void SetSortOrder(float order);

	//�������Ԃ��擾
	float GetSortOrder();

	/// <summary>
	/// �e�N�X�`���̐ݒ�
	/// </summary>
	/// <param name="pTexture">�e�N�X�`���̃|�C���^</param>
	/// <param name="left">�e�N�X�`���̍����W</param>
	/// <param name="right">�e�N�X�`���̉E���W</param>
	/// <param name="bottom">�e�N�X�`���̉����W</param>
	/// <param name="top">�e�N�X�`���̏���W</param>
	void Texture(CTexture* pTexture,int left, int right, int bottom, int top);

	void Render();//�`��

	//�Փˏ���
	virtual void Collision(CCollider* m, CCollider* o) {}

protected:
	EState mState;      //���

	float mVx, mVy;		//���x
private:
	CTexture* mpTexture;//�e�N�X�`��

	int mLeft, mRight, mBottom, mTop;//���A�E�A���A��

};

