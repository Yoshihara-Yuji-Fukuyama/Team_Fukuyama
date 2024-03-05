#pragma once

class CRectangle
{
public:
	CRectangle();
	~CRectangle();

	void Render();

	/// <summary>
	/// �l�p�`�̕`��
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	void Render(float x, float y, float w, float h);

	/// <summary>
	/// �傫���̐ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	void Set(float x, float y, float w, float h);

	float GetX();
	float GetY();
	float GetW();
	float GetH();

private:
	float mX; //X���W
	float mY; //Y���W
	float mW; //��
	float mH; //����

};