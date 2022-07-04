#include "stdafx.h"
#include "CollectItem.h"
#include "EdgeManagement.h"
#include "Player.h"
#include "Game.h"
#include "Bell.h"

namespace
{
	const int NUM_ANIMATIONCLIP = 0;								// �A�j���[�V�����N���b�v�̐�
	const int MAX_INSTANCE = 0;
	const int EDGE_COLOR_WHITE = 0;									// �֊s���̐F(��)
	const int EDGE_COLOR_YELLOW = 2;								// �֊s���̐F(��)
	const Vector3 ITEM_MODEL_SCALE = { 5.0f,5.0f,5.0f };			// ���f���̊g�嗦
	const float PLAYER_POSSIBLE_GET_ITEM_DISTANCE_TO_ITEM = 100.0f;	// �v���C���[���A�C�e�����擾�\�ȋ���
	const float TIME_TO_DRAW_AGAIN_PER_SEC = 5.0f;					// �Ăѕ`�悷��܂ł̎��ԁB(�P��:�b)
	const float MINIMUM_TIMER_VALUE = 0.0f;							// �^�C�}�[�̍Œ�l
	const int LOW_POINT = 1;										// �Ⴂ�|�C���g���擾�������ɑ������l�B
	const int HIGH_POINT = 3;										// �����|�C���g���擾�������ɑ������l�B
	const float COLOR_CHANGE_DISTANCE_TO_PLAYER = 500.0f;			// �F��ύX����v���C���[�Ƃ̋���
}

bool CollectItem::Start()
{
	// ���f���̏������B
	m_itemModel.Init(
		"Assets/modelData/item/bell.tkm",
		nullptr,
		NUM_ANIMATIONCLIP,
		enModelUpAxisZ,
		MAX_INSTANCE,
		EDGE_COLOR_WHITE,
		m_edgeManagement->GetEdgeControl()
	);
	// ���f���̊g�嗦��ݒ�B
	m_itemModel.SetScale(ITEM_MODEL_SCALE);

	// �v���C���[�̃C���X�^���X�������B
	m_player = FindGO<Player>("player");

	// �Q�[���̃C���X�^���X�������B
	m_game = FindGO<Game>("game");

	// �v���C���[�����x���̃C���X�^���X�������B
	m_bell = FindGO<Bell>("bell");

	// ���݂̗֊s���̐F�����ł��邱�Ƃ�ێ�����B
	m_currentColor = EDGE_COLOR_WHITE;

	return true;

}

void CollectItem::Update()
{
	// �`�悳��Ă��Ȃ��Ȃ�΁B
	if (m_isDraw == false) {
		// �o������܂ł̎��Ԃ𒲂ׂ�B
		CountAppearsAgain();
		// �ȍ~�̏������s��Ȃ��B
		return;
	}
	// �A�C�e�����擾�B
	RetrieveItem();

	// �F��ύX���邩���ׂ�B
	CheckChangeColor();

	// ��]������B
	Rotation();

	// ���W��ݒ�B
	m_itemModel.SetPosition(m_position);

	// ���f���̍X�V�B
	m_itemModel.Update();
}

void CollectItem::Rotation()
{
	// ��]�����Z�B
	m_rotation.AddRotationDegY(1.5f);
	// ���f���ɉ�]�̒l��ݒ�B
	m_itemModel.SetRotation(m_rotation);
}

void CollectItem::CheckDistanceToPlayer()
{
	// �v���C���[�̍��W�B
	m_playerPos = m_player->GetPosition();
	// �v���C���[�Ƃ̋����B
	m_distToPlayer = m_position - m_playerPos;

}

void CollectItem::RetrieveItem()
{
	// �v���C���[�Ƃ̋����𒲂ׂ�B
	CheckDistanceToPlayer();

	// �v���C���[���A�C�e�����擾����Ȃ�΁B
	if (m_distToPlayer.Length() < PLAYER_POSSIBLE_GET_ITEM_DISTANCE_TO_ITEM) {
		// ���݂̐F�����Ȃ�΁B
		if (m_currentColor == EDGE_COLOR_WHITE) {
			// �X�R�A��1���₷�B
			m_game->AddScore(LOW_POINT);
		}
		// ���݂̐F�����Ȃ�΁B
		else if (m_currentColor == EDGE_COLOR_YELLOW) {
			// �X�R�A��3���₷�B
			m_game->AddScore(HIGH_POINT);
		}

		// �`������Ȃ��悤�ɂ���B
		m_isDraw = false;
		// �Ăѕ`�悳���܂ł̃^�C�}�[�����Z�b�g�B
		m_drawAgainTimerPerSec = TIME_TO_DRAW_AGAIN_PER_SEC;
	}
}

void CollectItem::CheckChangeColor()
{
	// �v���C���[�Ƃ̋����𒲂ׂ�B
	CheckDistanceToPlayer();

	// �v���C���[���x����炵�Ă��邩�B
	bool isBellRing = m_bell->IsBellRinging();

	// ���݂̐F�����Ȃ�ΐF�𔒂ɖ߂����߂̃^�C�}�[��i�߂�B
	if (m_currentColor == EDGE_COLOR_YELLOW) {
		m_resetColorTimerPerSec -= g_gameTime->GetFrameDeltaTime();
	}

	// �v���C���[���x����炵�Ă��鎞�ɋ������߂��A���݂̐F�����Ȃ�΁B
	if (m_distToPlayer.Length() < COLOR_CHANGE_DISTANCE_TO_PLAYER 
		&& m_currentColor == EDGE_COLOR_WHITE
		&& isBellRing == true
		) 
	{
		// ���f��������������B(�֊s���̐F�͉�)
		m_itemModel.Init(
			"Assets/modelData/item/bell.tkm",
			nullptr,
			NUM_ANIMATIONCLIP,
			enModelUpAxisZ,
			MAX_INSTANCE,
			EDGE_COLOR_YELLOW,
			m_edgeManagement->GetEdgeControl()
		);
		// ���݂̐F��ێ�����B
		m_currentColor = EDGE_COLOR_YELLOW;
		// �F�����Z�b�g����^�C�}�[������������B
		m_resetColorTimerPerSec = 5.0f;

	}
	// �v���C���[�Ƃ̋����������A���݂̐F�����Ȃ�΁B
	else if (m_currentColor == EDGE_COLOR_YELLOW
		&& m_resetColorTimerPerSec <= 0.0f
		)
	{
		// ���f��������������B(�֊s���̐F�͔�)
		m_itemModel.Init(
			"Assets/modelData/item/bell.tkm",
			nullptr,
			NUM_ANIMATIONCLIP,
			enModelUpAxisZ,
			MAX_INSTANCE,
			EDGE_COLOR_WHITE,
			m_edgeManagement->GetEdgeControl()
		);
		m_currentColor = EDGE_COLOR_WHITE;
	}
	
}

void CollectItem::CountAppearsAgain()
{
	// �Ăѕ`�悳���܂ł̃^�C�}�[�̒l�����炷�B
	m_drawAgainTimerPerSec -= g_gameTime->GetFrameDeltaTime();

	if (m_drawAgainTimerPerSec <= MINIMUM_TIMER_VALUE) {
		// �`�悷��悤�ɐݒ肷��B
		m_isDraw = true;
	}
}

void CollectItem::Render(RenderContext& rc)
{
	// �`�悵�Ȃ��悤�ɂȂ��Ă���Ȃ�΁B
	if (m_isDraw == false) {
		// �`�悵�Ȃ��B
		return;
	}
	// ���f���̕`��B
	m_itemModel.Draw();
}