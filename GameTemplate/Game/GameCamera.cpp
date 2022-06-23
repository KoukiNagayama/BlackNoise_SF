#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace {
	const float TO_CAMERA_POSITION_X_FROM_TARGET = 0.0f;	// �����_���王�_�ւ̃x�N�g����X�v�f
	const float TO_CAMERA_POSITION_Y_FROM_TARGET = 0.0f;	// �����_���王�_�ւ̃x�N�g����Y�v�f
	const float TO_CAMERA_POSITION_Z_FROM_TARGET = -77.0f;	// �����_���王�_�ւ̃x�N�g����Z�v�f
	const float FAR_CLIP = 10000.0f;						// ������
	const float NEAR_CLIP = 3.0f;							// �ߕ���
	const float CAMERA_SPEED_MULTIPLIER = 1.5f;				// �J�����̉�]���x�̔{��
	const float CAMERA_ANGLE_MULTIPLIER = 1.3f;				// �J�����̊p�x�̔{��
	const float CAMERA_ROTATION_UPPER_LIMIT = 0.35f;		// �J�����̉�]�̏�̏��
	const float CAMERA_ROTATION_LOWER_LIMIT = -0.7f;		// �J�����̉�]�̉��̏��
	const float CAMERA_POSITION_Y = 250.0f;					// ���_�̍���
}

bool GameCamera::Start()
{
	// �����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(
		TO_CAMERA_POSITION_X_FROM_TARGET,
		TO_CAMERA_POSITION_Y_FROM_TARGET,
		TO_CAMERA_POSITION_Z_FROM_TARGET
	);

	// �ߕ��ʂ܂ł̋�����ݒ�B
	g_camera3D->SetNear(NEAR_CLIP);
	// �����ʂ܂ł̋�����ݒ�B
	g_camera3D->SetFar(FAR_CLIP);

	//m_position.y = 

	// �v���C���[������
	m_player = FindGO<Player>("player");
	return true;
}

void GameCamera::Update()
{
	// �ړ�
	Move();

	// �����_��ύX
	ViewPoint();

	g_camera3D->Update();
}

void GameCamera::Move()
{
	// 1�l�̎��_�̈׃J�����̓v���C���[�̍��W�����B
	m_position = m_player->GetPosition();

	// ���_�̍������グ��
	m_position.y = CAMERA_POSITION_Y;

	g_camera3D->SetPosition(m_position);
}

void GameCamera::ViewPoint()
{
	// �Â������_���王�_�܂ł̃x�N�g��
	Vector3 toCameraPosOld = m_toCameraPos;

	float x = g_pad[0]->GetRStickXF() * CAMERA_SPEED_MULTIPLIER;
	float y = g_pad[0]->GetRStickYF() * CAMERA_SPEED_MULTIPLIER;

	// Y������̉�]�B
	Quaternion qRot;
	// Degree�P�ʂŉ�]�N�H�[�^�j�I�����쐬�B
	qRot.SetRotationDeg(Vector3::AxisY, CAMERA_ANGLE_MULTIPLIER * x);
	// �����_���王�_�ɐL�т�x�N�g���ɍ쐬������]�N�H�[�^�j�I����K�p����B
	qRot.Apply(m_toCameraPos);

	// X������̉�]�B
	Vector3 axisX;
	// Y���ƒ����_����L�т�x�N�g���̊O�ς��v�Z�����K������B
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	// Degree�P�ʂŉ�]�N�H�[�^�j�I�����쐬�B
	qRot.SetRotationDeg(axisX, CAMERA_ANGLE_MULTIPLIER * -y);
	// �����_���王�_�ɐL�т�x�N�g���ɍ쐬������]�N�H�[�^�j�I����K�p����B
	qRot.Apply(m_toCameraPos);
	m_rotation = qRot;

	// ��]�̏���𒴂����Ȃ��
	if (RotationLimit() == false) {
		// �J�����̒����_��ς��Ȃ�
		m_toCameraPos = toCameraPosOld;
	}

	// �����_���v�Z����
	m_target = m_position + m_toCameraPos;

	// �����_��ݒ�
	g_camera3D->SetTarget(m_target);

}

bool GameCamera::RotationLimit()
{
	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();

	// �J�����̏���𒴂��Ă��邩�B
	if (toPosDir.y < CAMERA_ROTATION_LOWER_LIMIT
		|| toPosDir.y > CAMERA_ROTATION_UPPER_LIMIT
		) 
	{
		return false;
	}
	// �����Ă��Ȃ��B
	return true;
}
