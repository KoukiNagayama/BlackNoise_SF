#pragma once
class Player;
class Bell : public IGameObject
{
public:
	Bell() {};
	~Bell() {};
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
	/// �v���C���[�ɍ��킹�Ĉړ��B
	/// </summary>
	void MoveWithPlayer();
private:
	Player*				m_player = nullptr;				// �v���C���[�N���X�B
	ModelRender			m_bellModel;					// �x���̃��f��
	Vector3				m_position = Vector3::Zero;		// ���W
	
};

