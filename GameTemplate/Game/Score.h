#pragma once
class Game;
class Score : public IGameObject
{
public:
	Score() ;
	~Score() {};

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
	/// �\�������X�R�A�̍X�V�B
	/// </summary>
	void ScoreUpdate();
	/// <summary>
	/// �\�������n�C�X�R�A�̍X�V�B
	/// </summary>
	void HighScoreUpdate();
private:


private:
	SpriteRender			m_scoreNumberSprite[3];			// �X�R�A�̐���
	SpriteRender			m_highScoreNumberSprite[3];		// �n�C�X�R�A�̐���
	int						m_numberNum = -1;				// �����̐��i�ŏ��Ɍv�Z�j
	Game*					m_game = nullptr;				// �Q�[��
	int						m_score = 0;					// �X�R�A
	int						m_lastScore = 0;				// ���O�̃X�R�A
	int						m_highScore = 0;				// �n�C�X�R�A
	int						m_lastHighScore = 0;			// ���O�̃n�C�X�R�A
	SpriteRender			m_scoreSprite;					// SCORE�̃X�v���C�g
	SpriteRender			m_highScoreSprite;				// HIGHSCORE�̃X�v���C�g
};

