#include "stdafx.h"
#include "CollectItem.h"
#include "EdgeManagement.h"
#include "Player.h"
#include "Game.h"
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
	// �v���C���[�Ƃ̋����𒲂ׂ�B
	CheckDistanceToPlayer();

	// ��]������B
	Rotation();

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
	Vector3 playerPos = m_player->GetPosition();
	// �v���C���[�Ƃ̋����B
	Vector3 distToPlayer = m_position - playerPos;

	// �v���C���[���A�C�e�����擾����Ȃ�΁B
	if (distToPlayer.Length() < PLAYER_POSSIBLE_GET_ITEM_DISTANCE_TO_ITEM) {
		// �X�R�A�𑝂₷�B
		m_game->AddScore(1);
		// �`������Ȃ��悤�ɂ���B
		m_isDraw = false;
		// �Ăѕ`�悳���܂ł̃^�C�}�[�����Z�b�g�B
		m_drawAgainTimerPerSec = TIME_TO_DRAW_AGAIN_PER_SEC;
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