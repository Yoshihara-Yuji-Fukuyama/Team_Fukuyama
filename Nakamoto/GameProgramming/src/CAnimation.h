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
	/// <param name="direction">����</param>
	/// <param name="limit">���[�V�����̐�</param>
	/// <returns>�A�j���[�V�����ԍ�</returns>
	void MoveAnimation(int x, int y,
		bool moveX, bool moveY, float direction, int limit);

	/// <summary>
	/// �ҋ@�A�j���[�V����
	/// </summary>
	/// <param name="limit">���[�V�����̐�</param>
	/// <returns>�A�j���[�V�����ԍ�</returns>
	void WaitAnimation(int limit);

	/// <summary>
	/// �W�����v�A�j���[�V����
	/// </summary>
	/// <param name="y">Y���W</param>
	/// <param name="jump">�W�����v�O�̍��W</param>
	/// <param name="limit">���[�V�����̐�</param>
	/// <returns>�A�j���[�V�����ԍ�</returns>
	void JumpAnimation(int y, float jump, int limit);

	void AttackAnimation(int limit);

protected:
	//�A�j���[�V�����ԍ�
	CAnimationNumber mAnimationNum;
	//�t���[���J�E���^
	int mFrame;

private:
};
