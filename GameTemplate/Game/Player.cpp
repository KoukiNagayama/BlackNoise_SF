#include "stdafx.h"
#include "Player.h"
#include "GameCamera.h"

namespace
{
	const float PLAYER_RADIUS = 50.0f;			// �v���C���[�̔��a
	const float PLAYER_HEIGHT = 170.0f;			// �v���C���[�̍���
	const float WALK_SPEED = 500.0f;			// ��������
	const float FRICTION = 0.5f;				// ���C
	const float END_OF_MOVE = 0.001f;			// 1�t���[���̈ړ��ʂɂ���Ĉړ��I����\���x�N�g��
	const float Y_AXIS_MOVING_AMOUNT = 0.0f;	// Y���̈ړ���
}

bool Player::Start()
{
	// �L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(PLAYER_RADIUS, PLAYER_HEIGHT, m_position);

	m_gameCamera = FindGO<GameCamera>("gameCamera");
	return true;
}

void Player::Update()
{
	// �ړ�
	Move();

	Rotation();

	// �X�e�[�g�Ǘ�
	ManageState();
}

void Player::Move()
{
	// ���X�e�B�b�N�̓��͗ʂ��v�Z
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	// �J�����̑O�����ƉE�����̃x�N�g�����擾�B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	// Y�����ɂ͈ړ������Ȃ��B
	forward.y = Y_AXIS_MOVING_AMOUNT;
	right.y = Y_AXIS_MOVING_AMOUNT;

	// �ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed += right * stickL.x * WALK_SPEED;
	m_moveSpeed += forward * stickL.y * WALK_SPEED;

	// �ړ��ɖ��C��t�^����B
	m_moveSpeed.x -= m_moveSpeed.x * FRICTION;
	m_moveSpeed.z -= m_moveSpeed.z * FRICTION;

	// �ړ����x������l�ȉ���������
	if (m_moveSpeed.Length() < END_OF_MOVE)
	{
		// ����ɖ��C��t�^����B
		m_moveSpeed.x -= m_moveSpeed.x * FRICTION;
		m_moveSpeed.z -= m_moveSpeed.z * FRICTION;
	}

	// �L�����R�����g���č��W���ړ�������B
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
}

void Player::Rotation()
{
	//�J�����̌������擾
	Vector3 rotVec = m_gameCamera->GetToCameraPos();
	//y�̒l�̏��͗v��Ȃ��̂ŁA0.0f�������Đ��K���B
	rotVec.y = 0.0f;
	rotVec.Normalize();

	//���݂ǂꂾ����]���Ă���̂��̊p�x�����߂�B
	float angle = atan2(rotVec.x, rotVec.z);
	//���̊p�x���g���āAY������Quaternion��ݒ肷��B
	m_rotation.SetRotation(Vector3::AxisY, angle);
}

void Player::ManageState()
{
	switch (m_playerState) {
	case enPlayerState_Idle:
		break;
	case enPlayerState_Walk:
		break;
	case enPlayerState_Stop:
		break;
	}
}

void Player::Render(RenderContext& rc)
{

}
