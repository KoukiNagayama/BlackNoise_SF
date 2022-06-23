#pragma once
class BackGround : public IGameObject
{
public:
	BackGround() {};
	~BackGround() {};
	/// <summary>
	/// �J�n����
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);

private:
	ModelRender			m_inGameStage;
	Vector3				m_position = Vector3::Zero;
	Quaternion			m_rotation = Quaternion::Identity;
	Vector3				m_scale = Vector3::One;
};

