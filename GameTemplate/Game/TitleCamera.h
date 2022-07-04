#pragma once
class TitleText;
class TitleCamera : public IGameObject
{
public:
	TitleCamera() {};
	~TitleCamera() {};

	/// <summary>
	/// �J�n����
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// ���_��ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const Vector3& position)
	{
		m_cameraPos = position;
	}
	/// <summary>
	/// ���_���擾
	/// </summary>
	/// <returns>���W</returns>
	Vector3 GetPosition() const
	{
		return m_cameraPos;
	}
private:
	Vector3				m_cameraPos;			// ���W(���_)	
	Vector3				m_toCameraPos;			// �����_���王�_�Ɍ������x�N�g��
	TitleText*			m_tText = nullptr;		// �^�C�g���e�L�X�g
};

