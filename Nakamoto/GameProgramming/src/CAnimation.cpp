#include "CAnimation.h"


CAnimation::CAnimation()
	:mFrame(0)
{
}

//�ړ��A�j���[�V����
int CAnimation::MoveAnimation(int x, int y, bool moveX, bool moveY, float speed,int limit)
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 64;
	//���W��ۑ�
	int Pos = x;
	//Y���W�����ړ����Ă���Ȃ�Y���W������
	if (moveX == false && moveY == true)
	{
		Pos = y;
	}

	//���W��0�ȏ�̎�
	if (Pos >= 0)
	{
		if (Pos % PITCH < PITCH / limit)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				//���E��6�Ȃ�6����X�^�[�g
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move6;
				else AnimationNum = (int)CAnimationNumber::Move4;
			}
			//�E�ړ�
			else
			{
				AnimationNum = (int)CAnimationNumber::Move1;
			}
		}
		else if (Pos % PITCH < PITCH * 2 / limit)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move5;
				else AnimationNum = (int)CAnimationNumber::Move3;
			}
			//�E�ړ�
			else
			{
				AnimationNum = (int)CAnimationNumber::Move2;
			}
		}
		else if (Pos % PITCH < PITCH * 3 / limit)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move4;
				else AnimationNum = (int)CAnimationNumber::Move2;
			}
			//�E�ړ�
			else
			{
				AnimationNum = (int)CAnimationNumber::Move3;
			}
		}
		else if (Pos % PITCH < PITCH * 4 / limit)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move3;
				else AnimationNum = (int)CAnimationNumber::Move1;
			}
			//�E�ړ�
			else
			{
				AnimationNum = (int)CAnimationNumber::Move4;
			}
		}
		//���E��6�Ȃ�Ō�܂�
		else if (Pos % PITCH < PITCH * 5 / limit && limit == 6)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move2;
			}
			//�E�ړ�
			else
			{
				AnimationNum = (int)CAnimationNumber::Move5;
			}
		}
		else
		{
			//���ړ�
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move1;
			}
			//�E�ړ�
			else
			{
				AnimationNum = (int)CAnimationNumber::Move6;
			}
		}
	}
	//���W��0�����̎�
	else
	{
		//�����ɂ���
		Pos = -Pos;

		if (Pos % PITCH < PITCH / limit)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move1;
			}
			//�E�ړ�
			else
			{
				//���E��6�Ȃ�6����X�^�[�g
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move6;
				else AnimationNum = (int)CAnimationNumber::Move4;
			}
		}
		else if (Pos % PITCH < PITCH * 2 / limit)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move2;
			}
			//�E�ړ�
			else
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move5;
				else AnimationNum = (int)CAnimationNumber::Move3;
			}
		}
		else if (Pos % PITCH < PITCH * 3 / limit)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move3;
			}
			//�E�ړ�
			else
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move4;
				else AnimationNum = (int)CAnimationNumber::Move2;
			}
		}
		else if (Pos % PITCH < PITCH * 4 / limit)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move4;
			}
			//�E�ړ�
			else
			{
				if (limit == 6) AnimationNum = (int)CAnimationNumber::Move3;
				else AnimationNum = (int)CAnimationNumber::Move1;
			}
		}
		//���E��6�Ȃ�Ō�܂�
		else if (Pos % PITCH < PITCH * 5 / limit && limit == 6)
		{
			//���ړ�
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move5;
			}
			//�E�ړ�
			else
			{
				AnimationNum = (int)CAnimationNumber::Move2;
			}
		}
		else
		{
			//���ړ�
			if (speed < 0.0f)
			{
				AnimationNum = (int)CAnimationNumber::Move6;
			}
			//�E�ړ�
			else
			{
				AnimationNum = (int)CAnimationNumber::Move1;
			}
		}
	}
	return AnimationNum;
}

//�ҋ@�A�j���[�V����
int CAnimation::WaitAnimation(int limit)
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 48;
	int frame = mFrame++;

	if (frame % PITCH < PITCH / limit)
	{
		AnimationNum = (int)CAnimationNumber::Move1;
	}
	else if (frame % PITCH < PITCH * 2 / limit)
	{
		AnimationNum = (int)CAnimationNumber::Move2;
	}
	else if (frame % PITCH < PITCH * 3 / limit)
	{
		AnimationNum = (int)CAnimationNumber::Move3;
	}
	else
	{
		AnimationNum = (int)CAnimationNumber::Move4;
	}
	return AnimationNum;
}