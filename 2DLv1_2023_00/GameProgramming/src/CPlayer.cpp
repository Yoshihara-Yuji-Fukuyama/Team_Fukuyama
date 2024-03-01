#include "CPlayer.h"
#include "CApplication.h"

void CPlayer::Update()
{
	//スペースを押すと弾が出る
	if (mInput.Key(VK_SPACE))
	{
		CApplication::TaskManager()->Add(
			new CBullet(X(), Y() + H() + 10.0
				, 3.0f, 10.0f, 1396, 1420, 750, 592
				, CApplication::Texture()));
	}

	//Aを押すと左に動く
	if (mInput.Key('A'))
	{
		float x = X() - 4.0f;
		X(x);
	}

	//Dを押すと右に動く
	if (mInput.Key('D'))
	{
		float x = X() + 4.0f;
		X(x);
	}
}