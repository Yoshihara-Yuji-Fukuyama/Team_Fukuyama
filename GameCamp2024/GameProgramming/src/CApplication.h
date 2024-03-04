#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CFont.h"
#include "CInput.h"
#include "CMiss.h"
#include "CCharacterManager.h"
#include "CGame.h"
#include "CSound.h"
#include "CTaskManager.h"

class CApplication
{

public:
	void Start();

	void Update();

	enum class EState
	{
		ESTART,
		EPLAY,
		ECLEAR,
		EOVER,
	};
	
	//static���\�b�h�̐錾
	static CCharacterManager* CharacterManager();

	static CTexture* Texture();

	static CTaskManager* TaskManager();

private:
	EState mState;

	CGame* mpGame;

	CPlayer* mpPlayer;

	CEnemy* mpEnemy;

	CBullet* mpBullet;

	CMiss* mpMiss;

	CFont mFont;

	CInput mInput;

	CSound mSoundBgm; //BGM

	CSound mSoundOver; //�Q�[���I�[�o�[��

	//static�ϐ��̐錾
	static CCharacterManager mCharacterManager;

	static CTexture mTexture;

	static CTaskManager mTaskManager;
};