#pragma once
#include "CTexture.h"

class CCharacter
{
public:
	//有効フラグを返す
	bool Enabled();
	//デフォルトコンストラクタ
	CCharacter();
	//デストラクタ
	~CCharacter();

	CTexture* Texture();

	void Texture(CTexture* pTexture,
		int left, int right, int bottom, int top);

	virtual void Render();

	virtual void Update() = 0;

protected:
	bool mEnabled;//有効フラグ
private:
	CTexture* mpTexture;

	int mLeft, mRight, mBottom, mTop;

};
