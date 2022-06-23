#pragma once

#include "LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Bell;
class Game : public IGameObject
{
public:
	Game() {};
	~Game() {};
	/// <summary>
	/// �J�n����
	/// </summary>
	/// <returns>���������I�����Ă����true�B</returns>
	bool Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �Q�[���N���A���Ă��邩�B
	/// </summary>
	/// <returns>�Q�[���N���A�ɂȂ��Ă����true�B�����łȂ����false�B</returns>
	bool IsGameClearNow()
	{
		return m_gameState == enGameState_GameClear;
	}
	/// <summary>
	/// �Q�[���I�[�o�[���Ă��邩�B
	/// </summary>
	/// <returns>�Q�[���I�[�o�[�ɂȂ��Ă����true�B�����łȂ����false�B</returns>
	bool IsGameOverNow()
	{
		return m_gameState == enGameState_GameOver;
	}
private:
	/// <summary>
	/// �X�e�[�g�Ǘ�
	/// </summary>
	void ManageState();
	/// <summary>
	/// �^�C�g������̃X�e�[�g�J�ڏ���
	/// </summary>
	void StateTransitionProccesingFromTitle();
	/// <summary>
	/// �C���Q�[������̃X�e�[�g�J�ڏ���
	/// </summary>
	void StateTransitionProccesingFromInGame();
	/// <summary>
	/// �Q�[���G���h����̃X�e�[�g�J�ڏ���
	/// </summary>
	void StateTransitionProccesingFromGameEnd();
	/// <summary>
	/// �Q�[���I�[�o�[����̃X�e�[�g�J�ڏ���
	/// </summary>
	void StateTransitionProccesingFromGameOver();
	/// <summary>
	/// �C���Q�[����������
	/// </summary>
	void InitInGame();

private:
	enum EnGameState
	{
		enGameState_Title,			// �^�C�g��
		enGameState_InGame,			// �C���Q�[��
		enGameState_GameClear,		// �Q�[���N���A
		enGameState_GameOver,		// �Q�[���I�[�o�[
		enGameState_GameEnd			// �Q�[���G���h
	};	

	EnGameState			m_gameState = enGameState_Title;		// �Q�[���X�e�[�g
	bool				m_isResultDisplayFinished = false;		// ���U���g�̕\�����I�����Ă��邩
	bool				m_isEndGameOverProcess = false;			// �Q�[���I�[�o�[���̏������I�����Ă��邩
	LevelRender			m_inGameLevel;							// �C���Q�[���̃��x��
	Player*				m_player = nullptr;						// �v���C���[�N���X
	GameCamera*			m_gameCamera = nullptr;					// �Q�[���J�����N���X
	BackGround*			m_inGameStage = nullptr;				// �w�i�N���X
	Bell*				m_bell = nullptr;						// �x���N���X
};

