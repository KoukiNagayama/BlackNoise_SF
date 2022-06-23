#include "stdafx.h"
#include "Bell.h"
#include "Player.h"

namespace
{
	const float SHIFT_POSITION_FROM_CAMERA = 35.0f;				// �J�������炸�炷�l
	const float MODEL_POSITION_UP = 25.0f;						// �x����������ɂ�����
}

bool Bell::Start()
{
	// �v���C���[�������B
	m_player = FindGO<Player>("player");

	// �x���̃��f�����������B
	m_bellModel.Init(
		"Assets/modelData/item/bell.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		0
	);



	return true;
}

void Bell::Update()
{
	MoveWithPlayer();

	m_bellModel.Update();
}

void Bell::MoveWithPlayer()
{
	
	// ������x�N�g���B
	Vector3 up;
	// �E�����x�N�g���B
	Vector3 right;
	// �O�����x�N�g���B
	Vector3 forward;

	// �J�����̉E�������擾�B
	right = g_camera3D->GetRight();
	// �J�����̑O�������擾�B
	forward = g_camera3D->GetForward();
	// �J�����̏�������O�ςɂ���ċ��߂�B
	up.Cross(right, forward);
	up.Normalize();

	m_position = g_camera3D->GetPosition();
	// �x���̍��W�����炷�B
	m_position += g_camera3D->GetRight() * SHIFT_POSITION_FROM_CAMERA;
	m_position += g_camera3D->GetForward() * SHIFT_POSITION_FROM_CAMERA;
	m_position += up * MODEL_POSITION_UP;

	// �x���̍��W��ݒ�B
	m_bellModel.SetPosition(m_position);
	// �x���̉�]��ݒ�B
	m_bellModel.SetRotation(m_player->GetRotation());

}

void Bell::Render(RenderContext& rc)
{
	m_bellModel.Draw();
}
