#pragma once
#include "CTexture.h"
#include "CRectangle.h"
#include "CTask.h"

//�R���C�_�N���X�̐錾
class CCollider;

class CCharacter :public CRectangle, public CTask//�e�N���X��
{
public:
	enum class EState //���
	{
		EMOVE,		//�ړ�
		EJUMP,		//�W�����v
	};

	//�f�t�H���g�R���X�g���N�^
	CCharacter();
	//�f�X�g���N�^
	~CCharacter();
	//mpTexture��Ԃ�
	CTexture* GetTexture();
	
	//�L���t���O��Ԃ�
	bool GetEnabled();

	/// <summary>
	/// �w�i�̃R���X�g���N�^
	/// </summary>
	/// <param name="priority">�D��x</param>
	CCharacter(int priority);

	/// <summary>
	/// �e�N�X�`���̐ݒ�
	/// </summary>
	/// <param name="pTexture">�e�N�X�`���̃|�C���^</param>
	/// <param name="left">�e�N�X�`���̍����W</param>
	/// <param name="right">�e�N�X�`���̉E���W</param>
	/// <param name="bottom">�e�N�X�`���̉����W</param>
	/// <param name="top">�e�N�X�`���̏���W</param>
	void Texture(CTexture* pTexture, int left, int right, int bottom, int top);

	virtual void Render();//�`��
	//�Փˏ���
	virtual void Collision(CCollider* m, CCollider* o) {}

protected:
	bool mEnabled;//�L���t���O
	EState mState;	//���

	float mVx, mVy;		//���x
private:
	CTexture* mpTexture;//�e�N�X�`��

	int mLeft, mRight, mBottom, mTop;//���A�E�A���A��

};

