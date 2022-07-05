#pragma once
class Score : public IGameObject
{
public:
	Score() {};
	~Score() {};
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
private:
	/// <summary>
	/// 1�̈ʂ����߂�B
	/// </summary>
	void FindToOnesPlace();
	/// <summary>
	/// 10�̈ʂ����߂�B
	/// </summary>
	void FindToTensPlace();
	/// <summary>
	/// 100�̈ʂ����߂�B
	/// </summary>
	void FindToHundredthPlace();

private:
	SpriteRender			m_onesPlaceSprite;		// 1�̈ʂ̃X�v���C�g
	SpriteRender			m_tensPlaceSprite;		// 10�̈ʂ̃X�v���C�g
	SpriteRender			m_hundredthPlaceSprite;	// 100�̈ʂ̃X�v���C�g

	int						m_score;				// �X�R�A
	int						m_lastScore;			// ���O�̃X�R�A
};

