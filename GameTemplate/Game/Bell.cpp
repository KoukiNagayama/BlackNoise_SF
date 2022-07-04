#include "stdafx.h"
#include "Bell.h"
#include "Player.h"
#include "EdgeManagement.h"
#include "sound/SoundEngine.h"


namespace
{
	const float SHIFT_POSITION_FROM_CAMERA = 35.0f;				// �J�������炸�炷�l
	const float MODEL_POSITION_UP = 25.0f;						// �x����������ɂ�����
	const int	EDGE_COLOR_WHITE = 0;							// �֊s���̐F
	const int	NUM_ANIMATIONCLIP = 0;							// �A�j���[�V�����N���b�v�̐�
	const int	MAX_INSTANCE = 0;								// �C���X�^���X�̍ő吔
	const int	BELL_SOUND_NUMBER_TO_REGISTER = 0;				// �o�^����x���̉��̔ԍ�
	const float VOLUME = 1.0f;									// ����
	const float TIME_TO_BE_AVAILABLE_AGAIN_PER_SEC = 3.0f;	// �ēx�g�p�\�ɂȂ鎞��
}

Bell::~Bell()
{
	if (m_bellSound != nullptr) {
		DeleteGO(m_bellSound);
	}
}

bool Bell::Start()
{
	// �v���C���[�������B
	m_player = FindGO<Player>("player");

	// �x���̃��f�����������B
	m_bellModel.Init(
		"Assets/modelData/item/bell.tkm",
		nullptr,
		NUM_ANIMATIONCLIP,
		enModelUpAxisZ,
		MAX_INSTANCE,
		EDGE_COLOR_WHITE,
		m_edgeManagement->GetEdgeControl()
	);

	// �g�`�f�[�^��o�^����B
	g_soundEngine->ResistWaveFileBank(BELL_SOUND_NUMBER_TO_REGISTER, "Assets/sound/bell_low.wav");


	return true;
}

void Bell::Update()
{
	MoveWithPlayer();

	Ring();

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

void Bell::Ring()
{
	// �^�C�}�[�����炷�B
	m_availableAgainTimerPerSec -= g_gameTime->GetFrameDeltaTime();

	// B�{�^�����������Ƃ��Ƀ^�C�}�[��0�ɂȂ��Ă����
	if (g_pad[0]->IsTrigger(enButtonB) && m_availableAgainTimerPerSec <= 0.0f) {
		// ������炷�B
		m_bellSound = NewGO<SoundSource>(0);
		m_bellSound->Init(BELL_SOUND_NUMBER_TO_REGISTER);
		m_bellSound->SetVolume(VOLUME);
		m_bellSound->Play(false);

		// ���Ă���B
		m_isRing = true;
		// �^�C�}�[���ēx�������B
		m_availableAgainTimerPerSec = TIME_TO_BE_AVAILABLE_AGAIN_PER_SEC;
		return;
	}

	// ���Ă��Ȃ��B
	m_isRing = false;
}


void Bell::Render(RenderContext& rc)
{
	m_bellModel.Draw();
}
