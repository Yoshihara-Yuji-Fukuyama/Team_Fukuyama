#pragma once

class CTaskManager;

class CTask
{
	friend CTaskManager;
public:
	//�f�t�H���g�R���X�g���N�^
	CTask()
		:mpNext(nullptr), mpPrev(nullptr), mPriority(0), mEnabled(true) {}
	//�f�X�g���N�^
	virtual void Update() {}
	//�`��
	virtual void Render() {}
	//�Փ�
	virtual void Collision() {}
protected:
	int mPriority;//�D��x
	bool mEnabled;//�L���t���O
private:
	CTask* mpNext;//���̃|�C���^
	CTask* mpPrev;//�O�̃|�C���^
};