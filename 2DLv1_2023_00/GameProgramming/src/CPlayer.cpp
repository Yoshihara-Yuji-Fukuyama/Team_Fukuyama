#include "CPlayer.h"
#include "CApplication.h"

void CPlayer::Update()
{
	//�X�y�[�X�������ƒe���o��
	if (mInput.Key(VK_SPACE))
	{
		CApplication::TaskManager()->Add(
			new CBullet(X(), Y() + H() + 10.0
				, 3.0f, 10.0f, 1396, 1420, 750, 592
				, CApplication::Texture()));
	}

	//A�������ƍ��ɓ���
	if (mInput.Key('A'))
	{
		float x = X() - 4.0f;
		X(x);
	}

	//D�������ƉE�ɓ���
	if (mInput.Key('D'))
	{
		float x = X() + 4.0f;
		X(x);
	}
}