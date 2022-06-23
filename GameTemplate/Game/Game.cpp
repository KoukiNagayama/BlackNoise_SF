#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Bell.h"

bool Game::Start()
{

	return true;
}

void Game::Update()
{
	// �X�e�[�g�Ǘ�
	ManageState();

}

void Game::ManageState()
{
	switch (m_gameState) {
	// �^�C�g��
	case enGameState_Title:
		StateTransitionProccesingFromTitle();
		break;
	// �C���Q�[��
	case enGameState_InGame:
		StateTransitionProccesingFromInGame();
		break;
	// �Q�[���I�[�o�[
	case enGameState_GameOver:
		StateTransitionProccesingFromGameOver();
		break;
	// �Q�[���G���h
	case enGameState_GameEnd:
		StateTransitionProccesingFromGameEnd();
		break;
	default:
		break;
	}
}

void Game::StateTransitionProccesingFromTitle()
{
	// �Q�[���X�e�[�g���C���Q�[���ɕύX����B
	m_gameState = enGameState_InGame;
	// �C���Q�[��������������B
	InitInGame();
}

void Game::StateTransitionProccesingFromInGame()
{

}

void Game::StateTransitionProccesingFromGameOver()
{
	// �Q�[���I�[�o�[���̏������I�����Ă���Ȃ��
	if (m_isEndGameOverProcess) {
		// �Q�[���X�e�[�g���C���Q�[���ɕύX����B
		m_gameState = enGameState_InGame;
	}
}

void Game::StateTransitionProccesingFromGameEnd()
{
	// ���U���g�̕\�����I�����Ă���Ȃ��
	if (m_isResultDisplayFinished) {
		// �Q�[���X�e�[�g���^�C�g���ɕύX����B
		m_gameState = enGameState_Title;
	}
}

void Game::InitInGame()
{
	m_inGameLevel.Init("Assets/level3D/stage.tkl", [&](LevelObjectData& objData) {
		//�X�e�[�W
		if (objData.EqualObjectName(L"floor2") == true) {
			// �w�i�N���X
			m_inGameStage = NewGO<BackGround>(0, "backGround");
			return true;
		}
		//�v���C���[(�J����)
		if (objData.EqualObjectName(L"player") == true) {
			// �v���C���[�N���X
			m_player = NewGO<Player>(0, "player");
			m_player->SetPosition(objData.position);
			// �Q�[���J�����N���X
			m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
			m_gameCamera->SetPosition(objData.position);

			m_bell = NewGO<Bell>(0, "bell");
			return true;
		}
		// �G�l�~�[
		if (objData.ForwardMatchName(L"enemy") == true)
		{
			return true;
		}
		//�݂�
		if (objData.EqualObjectName(L"crashtoy") == true) {
			return true;
		}
		//�~���@
		if (objData.ForwardMatchName(L"gramophone") == true)
		{
			return true;
		}

		//���R�[�h
		if (objData.ForwardMatchName(L"record") == true)
		{
			return true;
		}
		if (objData.ForwardMatchName(L"door") == true)
		{
			return true;
		}
		if (objData.ForwardMatchName(L"switchfloor") == true)
		{
			return true;
		}
		if (objData.ForwardMatchName(L"gimmick") == true)
		{
			return true;
		}
		if (objData.EqualObjectName(L"crowbar") == true)
		{
			return true;
		}
	});


}
