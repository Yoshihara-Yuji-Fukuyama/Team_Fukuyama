#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CTask.h"

#define VELOCITY 2.0f   //�ړ����x

class CCharacter :public CRectangle,public CTask//�e�N���X��
{

public:

	bool Enabled();

	//�Փˏ���2
	virtual void Collision() {};

	//�Փˏ���4
	//Collision(�����̃|�C���^,�Փˑ���̃|�C���^)
	virtual void Collision(CCharacter* m, CCharacter* o) {};

	enum class ETag  //���ʎq
	{
		EZERO,       //�����l
		EBULLET,     //�e
		EENEMY,      //�I
		EPLAYER,     //�v���C���[
		ETURN,       //�܂�Ԃ�
		EBLOCK,      //�u���b�N
	};

	enum class EState //���
	{
		EMOVE,  //�ړ�
		ESTOP,  //��~
		EJUMP,  //�W�����v
		ECRY,  //����
	};
	//�f�t�H���g�R���X�g���N�^
	CCharacter();
	//�f�X�g���N�^
	~CCharacter();

	CTexture* Texture();

	void Texture(CTexture* pTexture,
		int left, int rihgt, int bottom, int top);

	virtual void Render();

	virtual void Update() = 0;

	void Move();

	ETag Tag();

	EState State(); //��Ԃ��擾����

protected:

	EState mState;

	ETag mTag;   //���ʎq

	bool mEnabled;//�L���t���O

	float mVy; //Y�����x

	float mVx; //X�����x

private:
	CTexture* mpTexture;

	int mLeft, mRight, mBottom, mTop;

};