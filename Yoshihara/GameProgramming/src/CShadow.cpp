#include "CShadow.h"

#define TEX_SHADOW 0,320,320,0 //影のテクスチャマッピング

CTexture CShadow::mTexture;

CTexture* CShadow::GetTexture()
{
	return &mTexture;
}

CShadow::CShadow()
	:CCharacter((int)CTaskPriority::Shadow)
{

}
CShadow::CShadow(float x,float y, float w, float h)
	:CShadow()
{
	Set(x, y, w, h);

	Texture(GetTexture(), TEX_SHADOW);
}

void CShadow::SetShadow(float x, float y, float w, float h)
{
	Set(x, y, w, h);
}