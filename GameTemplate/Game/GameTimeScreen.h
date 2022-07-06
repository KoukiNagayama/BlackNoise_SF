#pragma once

/// <summary>
/// �c�莞�Ԃ�\������N���X
/// 3���Ή�
/// </summary>
class GameTimeScreen : public IGameObject
{
public:
	GameTimeScreen();
	~GameTimeScreen();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(){};
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);

	/// <summary>
	/// �^�C�}�[�̏�Ԃ��X�V
	/// </summary>
	/// <param name="time">�\�����鎞��</param>
	void GameTimerUpdate(const float time);

private:
	
	SpriteRender m_numberSprite[3];		// �����摜
	int m_numberNum = -1;				// �����̐��i�ŏ��Ɍv�Z�j

	bool m_colorChangeFlag = false;		// �F�ύX�t���O

	int m_oldTime = -1;

};

