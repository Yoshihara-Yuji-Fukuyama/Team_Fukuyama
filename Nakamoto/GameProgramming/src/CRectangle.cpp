#include "CRectangle.h"
#include "glut.h"

//�R���X�g���N�^
CRectangle::CRectangle()
{

}

//�f�X�g���N�^
CRectangle::~CRectangle()
{

}

void CRectangle::Render()
{
	//�l�p�`�ŕ`��
	glBegin(GL_QUADS);
	glVertex2f(mX - mW, mY - mH);
	glVertex2f(mX + mW, mY - mH);
	glVertex2f(mX + mW, mY + mH);
	glVertex2f(mX - mW, mY + mH);
	glEnd();
}

void CRectangle::Render(float x, float y, float w, float h)
{
	glBegin(GL_QUADS);
	glVertex2f(mX - mW, mY - mH);
	glVertex2f(mX + mW, mY - mH);
	glVertex2f(mX + mW, mY + mH);
	glVertex2f(mX - mW, mY + mH);
	glEnd();
}

void CRectangle::Set(float x, float y, float w, float h)
{
	mX = x;
	mY = y;
	mW = w;
	mH = h;
}

float CRectangle::GetX()
{
	return mX;
}

float CRectangle::GetY()
{
	return mY;
}

float CRectangle::GetW()
{
	return mW;
}

float CRectangle::GetH()
{
	return mH;
}

void CRectangle::SetY(float y)
{
	mY = y;
}

void CRectangle::SetX(float x)
{
	mX = x;
}
