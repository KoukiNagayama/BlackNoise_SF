#pragma once
class EdgeManagement;
class BackGround : public IGameObject
{
public:
	BackGround() {};
	~BackGround();
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
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �֊s���ɉe����^�������ݒ�B
	/// </summary>
	/// <param name="edgeManagement">�֊s���ɉe����^������</param>
	const void SetEdgeManagement(EdgeManagement* edgeManagement)
	{
		m_edgeManagement = edgeManagement;
	}
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
private:
	ModelRender				m_inGameStage;							// �X�e�[�W�̃��f��
	Vector3					m_position = Vector3::Zero;				// ���W
	Quaternion				m_rotation = Quaternion::Identity;		// ��]
	Vector3					m_scale = Vector3::One;					// �g�嗦
	EdgeManagement*			m_edgeManagement = nullptr;				// �֊s���ɉe����^������
	PhysicsStaticObject		m_physicsStaticObject;					// �ÓI�����I�u�W�F�N�g								
};

