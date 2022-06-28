#pragma once

#include "sound/SoundSource.h"

class GameCamera;
class Player : public IGameObject
{
public:
	Player();
	~Player();
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
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="x">x���W�B</param>
	/// <param name="y">y���W�B</param>
	/// <param name="z">z���W�B</param>
	void SetPosition(float x, float y, float z)
	{
		SetPosition({ x, y, z });
	}
	/// <summary>
	/// ���W���擾�B
	/// </summary>
	/// <returns>�v���C���[�̍��W</returns>
	const Vector3& GetPosition() const 
	{
		return m_position;
	}
	const Quaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// �v���C���[�̑��������Ă��邩�B
	/// </summary>
	/// <returns>���Ă����true�B���Ă��Ȃ����false�B</returns>
	bool IsPlayerFootstepSound() const
	{
		return m_isFootstepSound;
	}
private:
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();
	/// <summary>
	/// ��]�����B
	/// </summary>
	void Rotation();
	/// <summary>
	/// �X�e�[�g�Ǘ��B
	/// </summary>
	void ManageState();
	/// <summary>
	/// �X�e�[�g���Ƃ̏����B
	/// </summary>
	void ProcessByState();
	/// <summary>
	/// ���ʂ̃X�e�[�g�J�ڏ����B
	/// </summary>
	void ProcessCommonStateTransition();
	/// <summary>
	/// ������炷�B
	/// </summary>
	void PlayFootstepSound();
	/// <summary>
	/// �������~�߂�B
	/// </summary>
	void StopFootstepSound();

private:
	enum EnPlayerState {
		enPlayerState_Idle,		// �ҋ@
		enPlayerState_Walk,		// ����
		enPlayerState_Stop		// ��~
	};
	GameCamera*				m_gameCamera = nullptr;				// �Q�[���J�����N���X
	Vector3					m_position = Vector3::Zero;			// ���W
	Quaternion				m_rotation = Quaternion::Identity;	// ��]
	Vector3					m_moveSpeed = Vector3::Zero;		// �ړ����x
	CharacterController		m_charaCon;							// �L�����N�^�[�R���g���[���[
	EnPlayerState			m_playerState = enPlayerState_Idle;	// �v���C���[�X�e�[�g
	SoundSource*			m_footstepSound = nullptr;			// ����
	bool					m_isFootstepSound = false;
};

