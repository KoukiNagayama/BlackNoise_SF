#include "stdafx.h"
#include "GameOverEffect.h"
#include "Player.h"
#include "Enemy.h"
#include "GameCamera.h"

namespace
{
	const float CAMERA_TARGET_Y_UP = 280.0f;					// �ŏI�����_��Y�␳��
	const float CAMERA_TARGET_MOVE_TIME = 8.0f;					// �^�[�Q�b�g����������

	const Vector3 CAMERA_CATCH_SHAKE = { 40.0f,40.0f,40.0f };	// �߂܂������̃V�F�C�N��
	const float CAMERA_CATCH_SHAKE_TIME = 0.24f;				// �߂܂������̃V�F�C�N����
	const float CAMERA_CATCH_MUL = 0.63f;						// �߂܂������̃V�F�C�N�ʂɏ�Z����i���񂾂񏬂�������j

	const Vector3 CAMERA_ALWAYS_SHAKE = { 3.0f,3.0f,3.0f };		// �펞�V�F�C�N��
}

void GameOverEffect::StartGameOverEffect() {

	m_isPlayEffect = true;

	// �v���C���[�ƃJ�������ړ��s�\�ɂ���
	m_player->SetIsMovable(false);
	m_gameCamera->SetIsMovable(false);

	// �ړ��ʂ��v�Z
	Vector3 target_pos = m_enemy->GetPosition();
	target_pos.y += CAMERA_TARGET_Y_UP;
	m_cameraTargetMove = (target_pos - g_camera3D->GetPosition()) / CAMERA_TARGET_MOVE_TIME;
	// ���t���[���̒����_��ۑ����Ă���
	m_cameraNextTarget = g_camera3D->GetTarget() + m_cameraTargetMove;

	// �ړ��^�C�}�[��������
	m_cameraTargetMoveTimer = CAMERA_TARGET_MOVE_TIME;

	// �V�F�C�N�^�C�}�[��������
	m_cameraCatchShakeTimer = CAMERA_CATCH_SHAKE_TIME;

	// �V�F�C�N�ʂ�������
	m_cameraShake = CAMERA_CATCH_SHAKE;

}

void GameOverEffect::PlayGameOverEffect() {

	// �߂܂����u�ԑ傫���V�F�C�N
	if (m_cameraCatchShakeTimer > 0.0f) {
		m_cameraCatchShakeTimer -= g_gameTime->GetFrameDeltaTime();
		// �V�F�C�N�ʂ͓K���ɗ���
		Vector3 shake = {
			(float)((rand() % ((int)m_cameraShake.x * 2)) - (int)m_cameraShake.x),
			(float)((rand() % ((int)m_cameraShake.y * 2)) - (int)m_cameraShake.y),
			(float)((rand() % ((int)m_cameraShake.z * 2)) - (int)m_cameraShake.z)
		};
		// ����������
		m_cameraShake *= CAMERA_CATCH_MUL;
		// 0�ɂȂ�ƃN���b�V�����Ă��܂��c
		m_cameraShake.x = max(m_cameraShake.x, 1.0f);
		m_cameraShake.y = max(m_cameraShake.y, 1.0f);
		m_cameraShake.z = max(m_cameraShake.z, 1.0f);
		// �ݒ肷��
		g_camera3D->SetTarget(m_cameraNextTarget + shake);
	}
	else {

		// �J�������^�[�Q�b�g�Ɍ�������
		if (m_cameraTargetMoveTimer > 0.0f) {
			m_cameraTargetMoveTimer -= g_gameTime->GetFrameDeltaTime();
			// �ݒ�
			g_camera3D->SetTarget(m_cameraNextTarget);
			// ���t���[���̒����_��ۑ����Ă���
			m_cameraNextTarget = g_camera3D->GetTarget() + m_cameraTargetMove;
		}

		// �펞�����ɃV�F�C�N
		Vector3 shake = {
			(float)((rand() % ((int)CAMERA_ALWAYS_SHAKE.x * 2)) - (int)CAMERA_ALWAYS_SHAKE.x),
			(float)((rand() % ((int)CAMERA_ALWAYS_SHAKE.y * 2)) - (int)CAMERA_ALWAYS_SHAKE.y),
			(float)((rand() % ((int)CAMERA_ALWAYS_SHAKE.z * 2)) - (int)CAMERA_ALWAYS_SHAKE.z)
		};
		// �ݒ肷��
		g_camera3D->SetTarget(g_camera3D->GetTarget() + shake);

	}
}