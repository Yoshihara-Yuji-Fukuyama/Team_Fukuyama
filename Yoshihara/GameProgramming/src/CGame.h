#pragma once
#include "CTexture.h"
#include "CEnemy.h"
#include "CBackground.h"

/*
CGame�N���X
�Q�[���N���X
�Q�[���̃}�b�v���쐬���A
�L�����N�^��z�u����
*/

class CGame
{
public:
	void Update();

	void Start();

	CGame();

	~CGame();

private:
	CEnemy* mpEnemy;

	CBackground* mpBackground;

};
