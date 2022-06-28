#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Bell.h"
#include "Enemy.h"
#include "CollectItem.h"

namespace
{

}

bool Game::Start()
{
	
	return true;
}

void Game::Update()
{
	// �X�e�[�g�Ǘ�
	ManageState();

	if (m_gameState == enGameState_InGame) {
		m_edgeManagement.Update();
	}

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
	if (m_isGameOver) {
		m_gameState = enGameState_GameOver;
		DeleteInGameObject();
	}
}

void Game::StateTransitionProccesingFromGameOver()
{
	// �Q�[���I�[�o�[��������������B
	m_isGameOver = false;
	// �֊s������̓o�^�f�[�^���N���A����B
	m_edgeManagement.Clear();
	// ����̃X�R�A���n�C�X�R�A��荂����΁B
	if (m_score > m_highScore) {
		// �n�C�X�R�A���X�V�B
		m_highScore = m_score;
	}
	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_isEndGameOverProcess = true;
	}
	// �Q�[���I�[�o�[���̏������I�����Ă���Ȃ��
	if (m_isEndGameOverProcess) {
		// �Q�[���X�e�[�g���C���Q�[���ɕύX����B
		m_gameState = enGameState_Title;
		m_isEndGameOverProcess = false;
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
			m_inGameStage->SetPosition(objData.position);
			m_inGameStage->SetEdgeManagement(&m_edgeManagement);
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
			m_bell->SetEdgeManagement(&m_edgeManagement);
			return true;
		}
		// �G�l�~�[
		if (objData.ForwardMatchName(L"enemy") == true)
		{
			m_enemy = NewGO<Enemy>(0, "enemy");
			m_enemy->SetPosition(objData.position);
			m_enemy->SetNumber(objData.number);
			m_enemy->SetEdgeManagement(&m_edgeManagement);
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
		return false;
	});
 
	m_collectItem = NewGO<CollectItem>(0, "collectItem");
	m_collectItem->SetEdgeManagement(&m_edgeManagement);
	m_edgeManagement.Init();
}

void Game::DeleteInGameObject()
{
	auto& enemys = FindGOs<Enemy>("enemy");
	int enemySize = enemys.size();
	for (int i = 0; i < enemySize; i++) {
		m_enemy = enemys[i];
		DeleteGO(m_enemy);
	}

	auto& gameCameras = FindGOs<GameCamera>("gameCamera");
	int gameCameraSize = gameCameras.size();
	for (int i = 0; i < gameCameraSize; i++) {
		m_gameCamera = gameCameras[i];
		DeleteGO(m_gameCamera);
	}

	auto& bells = FindGOs<Bell>("bell");
	int bellSize = bells.size();
	for (int i = 0; i < bellSize; i++) {
		m_bell = bells[i];
		DeleteGO(m_bell);
	}

	auto& players = FindGOs<Player>("player");
	int playerSize = players.size();
	for (int i = 0; i < playerSize; i++) {
		m_player = players[i];
		DeleteGO(m_player);
	}

	auto& inGameStages = FindGOs<BackGround>("backGround");
	int stageSize = inGameStages.size();
	for (int i = 0; i < stageSize; i++) {
		m_inGameStage = inGameStages[i];
		DeleteGO(m_inGameStage);
	}

}

