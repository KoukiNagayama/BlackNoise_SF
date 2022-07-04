#pragma once
class EdgeManagement;
class TitleText : public IGameObject
{
public:
	TitleText() {};
	~TitleText() {};
	/// <summary>
	/// �J�n����
	/// </summary>
	bool Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc">�����_�����O�R���e�L�X�g</param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	const Vector3 GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �֊s���ɉe����^�������ݒ�B
	/// </summary>
	/// <param name="edgeManagement">�֊s���ɉe����^������B</param>
	const void SetEdgeManagement(EdgeManagement* edgeManagement)
	{
		m_edgeManagement = edgeManagement;
	}
private:
	ModelRender			m_textModel;			// ���f�������_�[
	Vector3				m_position;				// ���W
	Vector3				m_scale;				// �g�嗦
	Quaternion			m_rotation;				// ��]
	EdgeManagement*		m_edgeManagement = nullptr;
};

