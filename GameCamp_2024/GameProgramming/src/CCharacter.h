#pragma once
#include "CTexture.h"

class CCharacter
{
public:
	//�L���t���O��Ԃ�
	bool Enabled();
	//�f�t�H���g�R���X�g���N�^
	CCharacter();
	//�f�X�g���N�^
	~CCharacter();

	CTexture* Texture();

	void Texture(CTexture* pTexture,
		int left, int right, int bottom, int top);

	virtual void Render();

	virtual void Update() = 0;

protected:
	bool mEnabled;//�L���t���O
private:
	CTexture* mpTexture;

	int mLeft, mRight, mBottom, mTop;

};
