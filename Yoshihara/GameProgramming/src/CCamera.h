#pragma once

//��ʂɕ\������͈͂�ݒ�
class CCamera
{
public:
	/// <summary>
	/// �\���G���A�̐ݒ�
	/// </summary>
	/// <param name="Left">��</param>
	/// <param name="Right">�E</param>
	/// <param name="bottom">��</param>
	/// <param name="top">��</param>
	static void SetCamera(double left, double right
		, double bottom, double top);

	static void End();

};