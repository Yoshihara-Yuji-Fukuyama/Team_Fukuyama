#pragma once
#include "CRectangle.h"
#include "CTexture.h"

class CApplication
{

public:
	void Start();
	void Update();

private:
	CRectangle mRectangle;
	CTexture mTexture;
};