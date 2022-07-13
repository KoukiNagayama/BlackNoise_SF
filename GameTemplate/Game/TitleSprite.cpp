#include "stdafx.h"
#include "TitleSprite.h"

namespace
{
	const float TEXT_SPRITE_W = 1920.0f;							// �X�v���C�g�̉���
	const float TEXT_SPRITE_H = 1080.0f;							// �X�v���C�g�̏c��
	const Vector3 TEXT_SPRITE_POSITION = { 7.0f, -20.8f, 0.0f };	// �X�v���C�g��\��������W	
	const Vector3 TEXT_SPRITE_SCALE = { 0.9f, 0.9f, 0.9f };			// �X�v���C�g�̊g�嗦
	const float ALPHA_VALUE_TO_STOP_DRAWING = 0.0f;					// �`�����߂郿�l
	const float FADE_OUT_ALPHA_MULTIPLIER = 0.3f;					// �t�F�[�h�A�E�g���Ƀ��l�ɏ�Z����l
}

bool TitleSprite::Start()
{
	// �X�v���C�g������������B
	m_pressBToStartSprite.Init(
		"Assets/sprite/PRESS_B_TO_START.DDS",
		TEXT_SPRITE_W,
		TEXT_SPRITE_H
	);

	// �X�v���C�g�̍��W��ݒ肷��B
	m_pressBToStartSprite.SetPosition(TEXT_SPRITE_POSITION);

	// �X�v���C�g�̊g�嗦��ݒ肷��B
	m_pressBToStartSprite.SetScale(TEXT_SPRITE_SCALE);

	return true;
}

void TitleSprite::Update()
{
	// �X�v���C�g���X�V����B
	m_pressBToStartSprite.Update();
}

void TitleSprite::Render(RenderContext& rc)
{
	// �X�v���C�g��`�悷��B
	m_pressBToStartSprite.Draw(rc);
}
