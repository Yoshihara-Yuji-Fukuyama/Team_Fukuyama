#pragma once
#include "CCharacter.h"
#include <vector>

//CCharacterクラスのインスタンスを管理する

class CCharacterManager
{

public:

	//衝突処理1
	void Collision();

	//衝突処理3
	//Collision(衝突元のポインタ)
	void Collision(CCharacter* character);

	//Add(CCharacterのポインタ)
	//可変長配列の後ろに追加する
	void Add(CCharacter* c);

	//可変長配列にあるポインタのUpdate()を実行していく
	void Update();

	//可変長配列にあるポインタのRender()を実行していく
	void Render();

	void Delete();

	//全インスタンス削除
	void AllDelete();

private:

	//CCharacterのポインタの可変長配列
	std::vector<CCharacter*>mpCharacters;
};
