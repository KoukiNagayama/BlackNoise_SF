#pragma once
class GameOver : public IGameObject
{
public:
	GameOver() {};
	~GameOver() {};

	/// <summary>
	/// �J�n�����B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈���B
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �����͏I���������B
	/// </summary>
	/// <returns>�I�����Ă����true�B���Ă��Ȃ����false�B</returns>
	bool IsEndProcess()
	{
		return m_isEndGameOverProcess;
	}
private:
	/// <summary>
	/// �t�F�[�h�C���B
	/// </summary>
	void FadeIn();
	/// <summary>
	/// �t�F�[�h�A�E�g�B
	/// </summary>
	void FadeOut();
private:
	SpriteRender			m_gameOverSprite;				// �Q�[���I�[�o�[���̃X�v���C�g
	float					m_currentAlpha = 0.0f;			// ���݂̃��l
	float					m_timerToFadeOut = 0.0f;		// �t�F�[�h�A�E�g�Ɉڍs����܂ł̎���
	Vector3					m_gameOverSpritePosition;		// �Q�[���I�[�o�[�̃X�v���C�g��\��������W			
	Vector3					m_gameOverSpriteScale;			// �Q�[���I�[�o�[�̃X�v���C�g�̊g�嗦
	bool					m_isFadeOut = false;			// �t�F�[�h�A�E�g���邩
	bool					m_isEndGameOverProcess = false; // �Q�[���I�[�o�[�̏��������ׂďI���������B
};

