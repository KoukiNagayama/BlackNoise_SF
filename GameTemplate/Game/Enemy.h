#pragma once
class Enemy : IGameObject
{
public:
	Enemy() {};
	~Enemy() {};
	
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
	/// <param name="rc"></param>
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
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rotation">��]</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �G�l�~�[�̔ԍ���ݒ�
	/// </summary>
	/// <param name="number">�ԍ�</param>
	void SetNumber(const int& number)
	{
		m_enemyNumber = number;
	}
	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns>���W</returns>
	const Vector3 GetPosition()
	{
		return m_position;
	}
private:

private:
	// �X�e�[�g
	enum EnEnemyState {
		enEnemyState_Walk,				// ����	
		enEnemyState_Scream,			// ���K
		enEnemyState_Chase,				// �ǐ�
		enEnemyState_Survey,			// ����
		enEnemyState_ReturnToPath,		// �p�X�ړ��ɖ߂�
		enEnemyState_Attack,			// �U��
		enEnemyState_Num,				// �X�e�[�g�̐�
	};

	// �A�j���[�V����
	enum EnAnimationClip {
		enAnimationClip_Walk,			// ����
		enAnimationClip_Run,			// ����
		enAnimationClip_Scream,			// ���K
		enAnimationClip_Survey,			// ����
		enAnimationClip_Attack,			// �U��
		enAnimationClip_Num,			// �A�j���[�V�����̐�
	};

	Vector3					m_position = Vector3::Zero;				// ���W
	Quaternion				m_rotation = Quaternion::Identity;		// ��]
	Vector3					m_scale = Vector3::One;					// �g�嗦
	int						m_enemyNumber;							// ���x����œo�^���ꂽ�G�l�~�[�̔ԍ�
	AnimationClip			m_animationClips[enAnimationClip_Num];	// �A�j���[�V�����N���b�v
	Vector3					m_moveVector;							// �ړ��������
	Vector3					m_moveSpeed;							// �ړ����鑬��
	EnEnemyState			m_enemyState = enEnemyState_Walk;		// �X�e�[�g

};

