#include "CCharacterManager.h"



void CCharacterManager::Add(CCharacter* c)
{
	mpCharacters.push_back(c);
}



void CCharacterManager::Update()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Update();
	}
}



void CCharacterManager::Render()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		mpCharacters[i]->Render();
	}
}



void CCharacterManager::Collision()
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		//�Փˏ���2�̌Ăяo��
		mpCharacters[i]->Collision();
	}
}



void CCharacterManager::Collision(CCharacter* character)
{
	for (size_t i = 0; i < mpCharacters.size(); i++)
	{
		//�Փˏ���4�̌Ăяo��
		character->Collision(character, mpCharacters[i]);
	}
}



void CCharacterManager::Delete()
{
	//�C�e���[�^�̐���
	std::vector<CCharacter*>::iterator itr;

	//�C�e���[�^��擪��
	itr = mpCharacters.begin();

	//�Ō�܂ŌJ��Ԃ�
	while (itr != mpCharacters.end())
	{


		if ((*itr)->Enabled())
		{
			//����
			itr++;
		}


		else
		{
			//false�̎��A�C���X�^���X���폜
			delete* itr;
			
			//�z�񂩂�폜
			itr = mpCharacters.erase(itr);
		}

	}

}




void CCharacterManager::AllDelete()
{
	//�C�e���[�^�̐���
	std::vector<CCharacter*>::iterator itr;

	//�C�e���[�^��擪��
	itr = mpCharacters.begin();

	//�Ō�܂ŌJ��Ԃ�
	while (itr != mpCharacters.end())
	{
		//�C���X�^���X���폜
		delete* itr;

		//�z�񂩂�폜
		itr = mpCharacters.erase(itr);
	}
}