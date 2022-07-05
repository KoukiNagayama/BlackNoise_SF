#pragma once
class TitleSprite : public IGameObject
{
public:
	TitleSprite() {};
	~TitleSprite() {};

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
	SpriteRender				m_pressAToStartSprite;		// �X�v���C�g
	float						m_currentAlpha = 1.0f;		// ���݂̃��l
};

