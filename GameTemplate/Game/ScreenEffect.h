#pragma once
class Enemy;
class Player;
class ScreenEffect : public IGameObject
{
public:
	/// <summary>
	/// �J�n�����B
	/// </summary>
	bool Start();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈���B
	/// </summary>
	/// <param name="rc">�����_�����O�R���e�L�X�g�B</param>
	void Render(RenderContext& rc);
private:
	/// <summary>
	/// ���l��ύX����B
	/// </summary>
	void ChangeAlphaValue();
	/// <summary>
	/// �X�e�[�g�Ǘ�
	/// </summary>
	void ManageState();
	/// <summary>
	/// �X�e�[�g�J��
	/// </summary>
	void StateTransitionProccesing();
	void FadeIn();
	void FadeOut();
private:
	enum EnScreenEffectState {
		enState_FadeIn,
		enState_Fix,
		enState_FadeOut,
		enState_Idle
	};
	SpriteRender			m_screenEffect;								// �X�N���[���G�t�F�N�g�̃X�v���C�g
	float					m_currentAlpha = 0.0f;						// ���݂̃��l
	Enemy*					m_enemy1 = nullptr;
	Enemy*					m_enemy2 = nullptr;
	float					m_shortestDistanceToEnemy = 10000.0f;		// �G�l�~�[�Ƃ̍ŒZ����
	Vector3					m_playerPos;
	Player*					m_player = nullptr;
	EnScreenEffectState		m_enScreenEffectState = enState_Idle;
	float					m_alphaValueMultiplier = 0.0f;
};

