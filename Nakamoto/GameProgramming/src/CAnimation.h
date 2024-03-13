#pragma once

enum class CAnimationNumber
{
	Move1,
	Move2,
	Move3,
	Move4,
	Move5,
	Move6,
};

class CAnimation
{
public:
	CAnimation();

	/// <summary>
	/// �ړ��A�j���[�V����
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="moveX">X�������Ă��邩</param>
	/// <param name="moveY">Y�������Ă��邩</param>
	/// <param name="speed">�ړ����x</param>
	/// <param name="limit">���[�V�����̐�</param>
	int MoveAnimation(int x, int y, 
		bool moveX, bool moveY, float speed,int limit);

	int WaitAnimation(int limit);

private:
	//�A�j���[�V�����̔ԍ�
	int AnimationNum;
	//�t���[���J�E���^
	int mFrame;
};
