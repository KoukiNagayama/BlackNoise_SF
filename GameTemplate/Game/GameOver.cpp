#include "stdafx.h"
#include "GameOver.h"

namespace
{
	const Vector3 SPRITE_POSITION = Vector3::Zero;			// �X�v���C�g��\��������W�B
	const Vector3 SPRITE_SCALE = Vector3::One;				// �X�v���C�g�̊g�嗦�B
	const float	  GAME_OVER_SPRITE_W = 1920.0f;				// �X�v���C�g�̉����B
	const float   GAME_OVER_SPRITE_H = 1080.0f;				// �X�v���C�g�̏c���B
	const float	  FADE_IN_ALPHA_MULTIPLIER = 0.5f;			// �t�F�[�h�C���̃��̔{���B
	const float   FADE_OUT_ALPHA_MULTIPLIER = 0.2f;			// �t�F�[�h�A�E�g�̃��̔{���B
	const float   FADE_OUT_TIMER_MAX_VALUE_PER_SEC = 1.5f;	// �t�F�[�h�A�E�g�Ɉڍs����^�C�}�[�̏������p�ő厞��
	const float	  MAX_ALPHA_VALUE = 1.0f;
	const float   MIN_ALPHA_VALUE = 0.0f;
}

bool GameOver::Start()
{
	// �X�v���C�g�̏�����
	m_gameOverSprite.Init(
		"Assets/sprite/Game_Over.DDS", 
		GAME_OVER_SPRITE_W, 
		GAME_OVER_SPRITE_H
	);
	// �X�v���C�g�̍��W��ݒ�B
	m_gameOverSprite.SetPosition(SPRITE_POSITION);
	// �X�v���C�g�̊g�嗦��ݒ�B
	m_gameOverSprite.SetScale(SPRITE_SCALE);
	// �^�C�}�[���������B
	m_timerToFadeOut = FADE_OUT_TIMER_MAX_VALUE_PER_SEC;

	return true;
}

void GameOver::Update()
{
	// ���l��1.0���Ⴂ�Ȃ��
	if (m_isFadeOut == false) {
		FadeIn();
	}
	else {
		// �t�F�[�h�A�E�g����܂ł̎��Ԃ��v�Z
		m_timerToFadeOut -=  g_gameTime->GetFrameDeltaTime();
		if (m_timerToFadeOut <= MIN_ALPHA_VALUE) {
			m_timerToFadeOut = MIN_ALPHA_VALUE;
			FadeOut();
		}
	}
}

void GameOver::FadeIn()
{
	// ���l�𑝂₷
	m_currentAlpha += FADE_IN_ALPHA_MULTIPLIER * g_gameTime->GetFrameDeltaTime();
	// ���l�����O�̎���1.0��荂���Ȃ����Ȃ��
	if (m_currentAlpha >= MAX_ALPHA_VALUE) {
		m_isFadeOut = true;
	}
}

void GameOver::FadeOut()
{
	// ���l�����炷
	m_currentAlpha -= FADE_OUT_ALPHA_MULTIPLIER * g_gameTime->GetFrameDeltaTime();
	// ���l�����O�̎���0.0���Ⴍ�Ȃ����Ȃ��
	if (m_currentAlpha <= MIN_ALPHA_VALUE) {
		m_isEndGameOverProcess = true;
	}
}

void GameOver::Render(RenderContext& rc)
{
	if (m_currentAlpha >= MIN_ALPHA_VALUE) {
		m_gameOverSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_currentAlpha });
		m_gameOverSprite.Draw(rc);
	}
}

