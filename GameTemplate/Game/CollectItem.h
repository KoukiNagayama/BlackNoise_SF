#pragma once
class EdgeManagement;
class Player;
class Game;
class CollectItem : public IGameObject
{
public:
	CollectItem() {}
	~CollectItem() {}

	/// <summary>
	/// �J�n�����B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈���B
	/// </summary>
	/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �֊s���ɉe����^�������ݒ�B
	/// </summary>
	/// <param name="edgeManagement">�֊s���ɉe����^������B</param>
	const void SetEdgeManagement(EdgeManagement* edgeManagement)
	{
		m_edgeManagement = edgeManagement;
	}
private:
	/// <summary>
	/// ��]�B
	/// </summary>
	void Rotation();
	/// <summary>
	/// �v���C���[�Ƃ̋����𒲂ׂ�B
	/// </summary>
	void CheckDistanceToPlayer();
	/// <summary>
	/// �Ăяo������܂ł̃J�E���g�B
	/// </summary>
	void CountAppearsAgain();
private:
	ModelRender				m_itemModel;							// �A�C�e���̃��f��
	Vector3					m_position = Vector3::Zero;				// ���W
	Quaternion				m_rotation = Quaternion::Identity;		// ��]
	Vector3					m_scale = Vector3::One;					// �g�嗦
	EdgeManagement*			m_edgeManagement = nullptr;				// �֊s������
	bool					m_isDraw = true;						// �`�悷�邩
	Player*					m_player = nullptr;						// �v���C���[
	float					m_drawAgainTimerPerSec = 0.0f;			// �Ăѕ`�悳���悤�ɂȂ�܂ł̃^�C�}�[(�P��:�b)
	Game*					m_game = nullptr;						// �Q�[��
};

