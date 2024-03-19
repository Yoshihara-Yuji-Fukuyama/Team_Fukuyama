#include "CAnimation.h"


CAnimation::CAnimation()
	:mFrame(0)
{
}

//�ړ��A�j���[�V����
void CAnimation::MoveAnimation(int x, int y, bool moveX, bool moveY, float direction,int limit)
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 192;
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
			if (direction < 0.0f)
			{
				//���E��6�Ȃ�6����
				if (limit == 6) mAnimationNum = CAnimationNumber::Move6;
				//���E��5�Ȃ�5����
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move5;
				else mAnimationNum = CAnimationNumber::Move4;
			}
			//�E�ړ�
			else
			{
				mAnimationNum = CAnimationNumber::Move1;
			}
		}
		else if (Pos % PITCH < PITCH * 2 / limit)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move5;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move4;
				else mAnimationNum = CAnimationNumber::Move3;
			}
			//�E�ړ�
			else
			{
				mAnimationNum = CAnimationNumber::Move2;
			}
		}
		else if (Pos % PITCH < PITCH * 3 / limit)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move4;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move3;
				else mAnimationNum = CAnimationNumber::Move2;
			}
			//�E�ړ�
			else
			{
				mAnimationNum = CAnimationNumber::Move3;
			}
		}
		else if (Pos % PITCH < PITCH * 4 / limit)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move3;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move2;
				else mAnimationNum = CAnimationNumber::Move1;
			}
			//�E�ړ�
			else
			{
				mAnimationNum = CAnimationNumber::Move4;
			}
		}
		//���E��5�ȏ�Ȃ瑱����
		else if (Pos % PITCH < PITCH * 5 / limit && limit >= 5)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				if (limit == 6)mAnimationNum = CAnimationNumber::Move2;
				else mAnimationNum = CAnimationNumber::Move1;
			}
			//�E�ړ�
			else
			{
				mAnimationNum = CAnimationNumber::Move5;
			}
		}
		//���E��6�ȏ�Ȃ瑱����
		else if (limit >= 6)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move1;
			}
			//�E�ړ�
			else
			{
				mAnimationNum = CAnimationNumber::Move6;
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
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move1;
			}
			//�E�ړ�
			else
			{
				//���E��6�Ȃ�6����X�^�[�g
				if (limit == 6) mAnimationNum = CAnimationNumber::Move6;
				//���E��5�Ȃ�5����
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move5;
				else mAnimationNum = CAnimationNumber::Move4;
			}
		}
		else if (Pos % PITCH < PITCH * 2 / limit)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move2;
			}
			//�E�ړ�
			else
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move5;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move4;
				else mAnimationNum = CAnimationNumber::Move3;
			}
		}
		else if (Pos % PITCH < PITCH * 3 / limit)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move3;
			}
			//�E�ړ�
			else
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move4;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move3;
				else mAnimationNum = CAnimationNumber::Move2;
			}
		}
		else if (Pos % PITCH < PITCH * 4 / limit)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move4;
			}
			//�E�ړ�
			else
			{
				if (limit == 6) mAnimationNum = CAnimationNumber::Move3;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move2;
				else mAnimationNum = CAnimationNumber::Move1;
			}
		}
		//���E��5�ȏ�Ȃ瑱����
		else if (Pos % PITCH < PITCH * 5 / limit && limit >= 5)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move5;
			}
			//�E�ړ�
			else
			{
				if (limit == 6)mAnimationNum = CAnimationNumber::Move2;
				else if (limit == 5)mAnimationNum = CAnimationNumber::Move1;
			}
		}
		//���E��6�ȏ�Ȃ瑱����
		else if (limit >= 6)
		{
			//���ړ�
			if (direction < 0.0f)
			{
				mAnimationNum = CAnimationNumber::Move6;
			}
			//�E�ړ�
			else
			{
				mAnimationNum = CAnimationNumber::Move1;
			}
		}
	}
}

//�ҋ@�A�j���[�V����
void CAnimation::WaitAnimation(int limit)
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 48;
	int frame = mFrame++;

	if (frame % PITCH < PITCH / limit)
	{
		mAnimationNum = CAnimationNumber::Move1;
	}
	else if (frame % PITCH < PITCH * 2 / limit)
	{
		mAnimationNum = CAnimationNumber::Move2;
	}
	else if (frame % PITCH < PITCH * 3 / limit)
	{
		mAnimationNum = CAnimationNumber::Move3;
	}
	else
	{
		mAnimationNum = CAnimationNumber::Move4;
	}
}

//�W�����v�A�j���[�V����
void CAnimation::JumpAnimation(int y, float jump, int limit)
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 270;
	//�W�����v�O�ƃW�����v���̍��W�̍������߂�
	int JumpPos = y - jump;


	if (JumpPos % PITCH < PITCH / limit)
	{
			mAnimationNum = CAnimationNumber::Move1;
	}
	else if (JumpPos % PITCH < PITCH * 2 / limit)
	{
		mAnimationNum = CAnimationNumber::Move2;
	}
	else if (JumpPos % PITCH < PITCH * 3 / limit)
	{
		mAnimationNum = CAnimationNumber::Move3;
	}
	else
	{
		mAnimationNum = CAnimationNumber::Move4;
	}
}


//�U���A�j���[�V����
void CAnimation::AttackAnimation(int limit)
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 72;
	int frame = mFrame++;

	if (frame % PITCH < PITCH / limit)
	{
		mAnimationNum = CAnimationNumber::Move1;
	}
	else if (frame % PITCH < PITCH * 2 / limit)
	{
		mAnimationNum = CAnimationNumber::Move2;
	}
	else if (frame % PITCH < PITCH * 3 / limit)
	{
		mAnimationNum = CAnimationNumber::Move3;
	}
	else if (frame % PITCH < PITCH * 4 / limit)
	{
		mAnimationNum = CAnimationNumber::Move4;
	}
	else if (frame % PITCH < PITCH * 5 / limit)
	{
		mAnimationNum = CAnimationNumber::Move5;
	}
	else if (frame % PITCH < PITCH * 6 / limit)
	{
		mAnimationNum = CAnimationNumber::Move6;
	}
	else
	{
		mAnimationNum = CAnimationNumber::END;
	}
	return;
}

//����A�j���[�V����
void CAnimation::DeathAnimation(int limit)
{
	//�摜��؂�ւ��鑬�x
	const int PITCH = 12;
	int frame = mFrame++;

	if (frame % PITCH < PITCH / limit)
	{
		mAnimationNum = CAnimationNumber::Move1;
	}
}