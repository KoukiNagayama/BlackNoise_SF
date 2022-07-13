#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Bell.h"
#include "Enemy.h"
#include "CollectItem.h"
#include "TitleCamera.h"
#include "TitleText.h"
#include "GameOver.h"
#include "TitleSprite.h"
#include "GameTimeScreen.h"
#include "GameOverEffect.h"
#include "Score.h"
#include "Result.h"
#include "sound/SoundEngine.h"
#include "ScreenEffect.h"

namespace
{
	const int SETTING_TIME_3_MIN_PER_SEC = 180.0f;				// �b���ƂŐ������Ԃ�3���ɐݒ�B
	const int SETTING_TIME_6_MIN_PER_SEC = 360.0f;				// �b���ƂŐ������Ԃ�5���ɐݒ�B	
	const int GAME_END_TIME_PER_FRAME = 0.0f;					// �t���[�����ƂŃQ�[�����I�����鎞��
	const int PICK_UP_BELL_NUMBER_TO_REGISTER = 9;				// �x�����擾�������̓o�^�ԍ�
	const int ESCAPE_SOUND_NUMBER_TO_REGISTER = 10;				// �������̉��̓o�^�ԍ�
	const float SOUND_VOLUME_MULTIPLIER = 0.3f;				// �������̉��̏�Z����l
	const float MAX_SOUND_VOLUME = 1.0f;						// �ő剹��
	const float MIN_SOUND_VOLUME = 0.0f;						// �ŏ�����
	const float MAX_SOUND_MUL_VOLUME = 0.7f;
	const float MIN_SOUND_MUL_VOLUME = 0.0f;
	const float CLOSE_TO_ENEMY_SOUND_NUMBER_TO_REGISTER = 11;	// �G���߂��Ȃ������̉��̓o�^�ԍ�
	const float CLOSE_TO_ENEMY_SOUND_RANGE = 2000.0f;			// �G���߂��Ȃ������ɒ������鉹�͈̔�
}

bool Game::Start()
{
	// �^�C�g�����������B
	StartTitle();
	
	// �g�`�f�[�^��o�^����B
	g_soundEngine->ResistWaveFileBank(PICK_UP_BELL_NUMBER_TO_REGISTER, "Assets/sound/pickup_bell.wav");
	g_soundEngine->ResistWaveFileBank(ESCAPE_SOUND_NUMBER_TO_REGISTER, "Assets/sound/escape_00.wav");
	g_soundEngine->ResistWaveFileBank(CLOSE_TO_ENEMY_SOUND_NUMBER_TO_REGISTER, "Assets/sound/normal_00.wav");

	// �c�莞�Ԃ�\������I�u�W�F�N�g���쐬�i�O�ʂɏo�����ߕ`�揇�Ԓx�߁j
	m_gameTimeScreen = NewGO<GameTimeScreen>(10, "gameTimeScreen");
	// ����`�悵�Ȃ��悤�ɏ�����
	m_gameTimeScreen->GameTimerUpdate(m_remainingTime);

	// �Q�[���I�[�o�[�G�t�F�N�g���쐬
	m_gameOverEffect = new GameOverEffect;

	// �X�R�A��\������
	m_scoreScreen = NewGO<Score>(11, "score");

	// �\������X�R�A���X�V�B
	m_scoreScreen->ScoreUpdate();
	m_scoreScreen->HighScoreUpdate();

	return true;
}

void Game::Update()
{
	// �X�e�[�g�Ǘ�
	ManageState();
	
	// �X�e�[�g���Ƃ̏���
	ProcessByState();

	// �������̉����Đ�����B
	PlayEscapeSound();

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

void Game::ProcessByState()
{
	switch (m_gameState) {
	case enGameState_Title:
		break;
	case enGameState_InGame:
		// �^�C�}�[��i�߂�B
		GameTimer();
		// �֊s������̏����X�V����B
		m_edgeManagement.Update();
		// �Q�[���I�[�o�[�G�t�F�N�g���Ȃ���s����
		if (m_gameOverEffect->IsPlayEffect()) {
			m_gameOverEffect->PlayGameOverEffect();
		}
		//CloseToEnemySoundVolumeControl();
		break;
	case enGameState_GameOver:
		// �^�C�}�[��i�߂�B
		GameTimer();
		break;
	case enGameState_GameEnd:
		GameTimer();
		break;
	}
}

void Game::StateTransitionProccesingFromTitle()
{
	if (g_pad[0]->IsTrigger(enButtonB)) {
		// �^�C�g���̃I�u�W�F�N�g���폜����B
		DeleteTitleObject();
		m_edgeManagement.Clear();
		// �Q�[���X�e�[�g���C���Q�[���ɕύX����B
		m_gameState = enGameState_InGame;
		// �C���Q�[��������������B
		InitInGame();
	}
}

void Game::StateTransitionProccesingFromInGame()
{

	// �c�莞�Ԃ������Ȃ�΁B
	if (m_remainingTime <= GAME_END_TIME_PER_FRAME) {
		// �X�e�[�g���Q�[���G���h�ɕύX����B
		m_gameState = enGameState_GameEnd;
		// �n�C�X�R�A�����߂�B
		if (m_highScore <= m_score) {
			m_highScore = m_score;
		}
		// �Q�[���I�u�W�F�N�g��S���폜����B
		DeleteInGameObject();
		// �^�C�}�[�̕`����~����B
		m_gameTimeScreen->SetDrawFlag(false);
		// ���U���g���쐬�B
		m_result = NewGO<Result>(0, "result");
		m_result->Init(m_highScore);
	}

	// �Q�[���I�[�o�[�ɂȂ��Ă���΁B
	if (m_isGameOver) {
		m_gameOver = NewGO<GameOver>(0, "gameOver");
		// �X�e�[�g���Q�[���I�[�o�[�ɕύX����B
		m_gameState = enGameState_GameOver;
		// �Q�[���I�u�W�F�N�g��S���폜����B
		DeleteInGameObject();
		// �Q�[���I�[�o�[�G�t�F�N�g�̌�n���B
		m_gameOverEffect->EndGameOverEffect();
		m_gameOverEffect->StopHorrorSound();
	}
}

void Game::StateTransitionProccesingFromGameOver()
{
	m_gameOver = FindGO<GameOver>("gameOver");
	// �Q�[���I�[�o�[��������������B
	m_isGameOver = false;
	// �֊s������̓o�^�f�[�^���N���A����B
	m_edgeManagement.Clear();

	// ����̃X�R�A���n�C�X�R�A��荂����΁B
	if (m_score > m_highScore) {
		// �n�C�X�R�A���X�V����B
		m_highScore = m_score;
	}

	// �X�R�A������������B
	m_score = 0;
	
	// �Q�[���I�[�o�[���̏������I�����Ă���Ȃ��
	if (m_gameOver->IsEndProcess()) {
		// �Q�[���X�e�[�g���C���Q�[���ɕύX����B
		m_gameState = enGameState_InGame;
		// �Q�[���I�[�o�[�̃C���X�^���X���폜����B
		DeleteGO(m_gameOver);
		// �C���Q�[��������������B
		InitInGame();
	}	
}

void Game::StateTransitionProccesingFromGameEnd()
{
	m_edgeManagement.Clear();

	if (g_pad[0]->IsTrigger(enButtonA)) {
		m_isResultDisplayFinished = true;
	}

	// ���U���g�̕\�����I�����Ă���Ȃ��
	if (m_isResultDisplayFinished) {
		// ���U���g���폜�B
		DeleteGO(m_result);
		// �Q�[���X�e�[�g���^�C�g���ɕύX����B
		m_gameState = enGameState_Title;
		// �^�C�g�������B
		StartTitle();
		// �^�C�}�[�̕`����ĊJ����B
		m_gameTimeScreen->SetDrawFlag(true);
		// �c�莞�Ԃ�n��
		m_gameTimeScreen->GameTimerUpdate(m_remainingTime);
		// ���Z�b�g���Ă���
		m_isResultDisplayFinished = false;
		m_gameTimeScreen->Reset();
		m_score = 0;
		m_highScore = 0;
	}
}

void Game::InitInGame()
{
	m_inGameLevel.Init("Assets/level3D/stage2_2.tkl", [&](LevelObjectData& objData) {
		//�X�e�[�W
		if (objData.EqualObjectName(L"stage") == true) {
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
		// ���W�A�C�e��
		if (objData.EqualObjectName(L"collectItem") == true)
		{
			auto collectItem = NewGO<CollectItem>(0, "collectItem");
			collectItem->SetPosition(objData.position);
			collectItem->SetEdgeManagement(&m_edgeManagement);
			m_collectItem.push_back(collectItem);
			return true;
		}
		return false;
	});
	
	// �֊s��������̏�����
	m_edgeManagement.Init();

/*	m_closeToEnemySound = NewGO<SoundSource>(0);
	m_closeToEnemySound->Init(CLOSE_TO_ENEMY_SOUND_NUMBER_TO_REGISTER);
	m_closeToEnemySound->SetVolume(MAX_SOUND_VOLUME);
	m_closeToEnemySound->Play(true);
*/
	//m_screenEffect = NewGO<ScreenEffect>(0, "screenEffect");

	// �Q�[���I�[�o�[�G�t�F�N�g�̏�����
	m_gameOverEffect->Init(m_player, m_enemy, m_gameCamera);

}

void Game::DeleteInGameObject()
{
	// �G�l�~�[�폜
	// �G�l�~�[�̏��
	auto& enemys = FindGOs<Enemy>("enemy");
	// �G�l�~�[�̐�
	int enemySize = enemys.size();
	for (int i = 0; i < enemySize; i++) {
		m_enemy = enemys[i];
		// �폜
		DeleteGO(m_enemy);
	}

	// �Q�[���J�����폜
	auto& gameCameras = FindGOs<GameCamera>("gameCamera");
	int gameCameraSize = gameCameras.size();
	for (int i = 0; i < gameCameraSize; i++) {
		m_gameCamera = gameCameras[i];
		DeleteGO(m_gameCamera);
	}

	for (auto collectItem : m_collectItem)
	{
		DeleteGO(collectItem);
	}
	m_collectItem.clear();

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

	DeleteGO(m_closeToEnemySound);

	//DeleteGO(m_screenEffect);

}

void Game::DeleteTitleObject()
{
	// �^�C�g���J�����폜
	// �^�C�g���J����������
	auto& titleCameras = FindGOs<TitleCamera>("titleCamera");
	// �^�C�g���J�����̐�
	int titleCameraSize = titleCameras.size();
	for (int i = 0; i < titleCameraSize; i++) {
		m_titleCamera = titleCameras[i];
		// �폜
		DeleteGO(m_titleCamera);
	}


	// �^�C�g���e�L�X�g�폜
	// �^�C�g���e�L�X�g������
	auto& titleTexts = FindGOs<TitleText>("titleText");
	// �^�C�g���e�L�X�g�̐�
	int titleTextSize = titleTexts.size();
	for (int i = 0; i < titleTextSize; i++) {
		m_titleText = titleTexts[i];
		// �폜
		DeleteGO(m_titleText);
	}

	// �X�e�[�W�폜
	// �X�e�[�W������
	auto& inGameStages = FindGOs<BackGround>("backGround");
	// �X�e�[�W�̐�
	int stageSize = inGameStages.size();
	for (int i = 0; i < stageSize; i++) {
		m_inGameStage = inGameStages[i];
		// �폜
		DeleteGO(m_inGameStage);
	}
	
	// �^�C�g���ɂ���X�v���C�g���폜
	DeleteGO(m_titleSprite);
}

void Game::GameTimer()
{

	// �c�莞�Ԃ��v�Z�B
	m_remainingTime -= g_gameTime->GetFrameDeltaTime();
	
	// �c�莞�Ԃ�n��
	m_gameTimeScreen->GameTimerUpdate(m_remainingTime);

}

void Game::StartGameOverEffect() {
	m_gameOverEffect->StartGameOverEffect();
}

void Game::StartTitle() {

	// ���Ԃ�ݒ�B
	m_remainingTime = SETTING_TIME_3_MIN_PER_SEC;

	m_titleLevel.Init("Assets/level3D/title.tkl", [&](LevelObjectData& objData)
		{
			// �^�C�g�����f��
			if (objData.EqualObjectName(L"titleText") == true) {
				m_titleText = NewGO<TitleText>(0, "titleText");
				m_titleText->SetPosition(objData.position);
				m_titleText->SetEdgeManagement(&m_edgeManagement);
				return true;
			}
			// �^�C�g���p�J����
			if (objData.EqualObjectName(L"titleCamera") == true) {
				m_titleCamera = NewGO<TitleCamera>(0, "titleCamera");
				m_titleCamera->SetPosition(objData.position);
				return true;
			}
			// �w�i
			if (objData.EqualObjectName(L"stage2") == true) {
				m_inGameStage = NewGO<BackGround>(0, "backGround");
				m_inGameStage->SetPosition(objData.position);
				m_inGameStage->SetEdgeManagement(&m_edgeManagement);
				return true;
			}
		});
	m_titleSprite = NewGO<TitleSprite>(0, "titleSprite");

	// �֊s�������������B
	m_edgeManagement.Init();
}

void Game::PlayEscapeSound()
{
	// �����Đ����邩
	bool isPlaySound = false;

	// �G�l�~�[������
	const auto& enemys = FindGOs<Enemy>("enemy");
	// �G�l�~�[�̐�
	const int size = enemys.size();

	// �C���Q�[���̎���
	if (m_gameState == enGameState_InGame) {
		for (int i = 0; i < size; i++) {
			m_enemy = enemys[i];
			// �Đ�����悤�ɐݒ肳��Ă���Ȃ�΁B
			if (m_enemy->IsChase()) {
				isPlaySound = true;
				break;
			}
		}
	}

	// �������Ă��Ȃ����ɖ�悤�ɐݒ肳�ꂽ�Ȃ�΁B
	if (isPlaySound && m_escapeSound == nullptr) {
		m_escapeSound = NewGO<SoundSource>(0);
		m_escapeSound->Init(ESCAPE_SOUND_NUMBER_TO_REGISTER);
		EscapeSoundVolumeControl(isPlaySound);
		m_escapeSound->Play(true);
	}

	// ���͖��Ă��邪�A���ʂ��������Ƃ��B
	if (isPlaySound && m_escapeSoundVolume < MAX_SOUND_VOLUME) {
		// �t�F�[�h�C��������B
		EscapeSoundVolumeControl(true);
	}
	// �������Ă��鎞�ɖ�Ȃ��悤�ɐݒ肳�ꂽ�Ȃ�΁B
	else if (isPlaySound == false && m_escapeSound != nullptr) {
		// �t�F�[�h�A�E�g������B
		EscapeSoundVolumeControl(false);
		if (m_escapeSoundVolume <= MIN_SOUND_VOLUME) {
			// �����폜�B
			DeleteGO(m_escapeSound);
			m_escapeSound = nullptr;
			// ���ʂ����Z�b�g�B
			m_escapeSoundVolume = MAX_SOUND_VOLUME;
		}
	}

}

void Game::EscapeSoundVolumeControl(bool fadeIn)
{

	if (fadeIn) {
		// �t�F�[�h�C���B
		m_escapeSoundVolume += SOUND_VOLUME_MULTIPLIER * g_gameTime->GetFrameDeltaTime();
		// ����l�𒴂���Ȃ�΁B
		if (m_escapeSoundVolume > MAX_SOUND_VOLUME) {
			// ���l���Œ肷��B
			m_escapeSoundVolume = MAX_SOUND_VOLUME;
		}
	}
	else {
		// �t�F�[�h�A�E�g�B
		m_escapeSoundVolume -= SOUND_VOLUME_MULTIPLIER * g_gameTime->GetFrameDeltaTime();

	}	
	// ���ʂ�ݒ肷��B
	m_escapeSound->SetVolume(m_escapeSoundVolume);
}

void Game::FadeCloseToEnemySound()
{
	// �t�F�[�h�C������Ȃ�΁B
	if (m_isFadeInCloseToEnemySound) {
		// �{�����[���ɏ�Z����l�𑝉�������B
		m_closeToEnemySoundMulVolume += g_gameTime->GetFrameDeltaTime();
		// �ő�l�𒴂��Ȃ��悤�ɌŒ肷��B
		if (m_closeToEnemySoundMulVolume >= MAX_SOUND_MUL_VOLUME) {
			m_closeToEnemySoundMulVolume = MAX_SOUND_MUL_VOLUME;
			m_isFadeInCloseToEnemySound = false;
		}
		return;
	}
	// �t�F�[�h�A�E�g����Ȃ�΁B
	else if (m_isFadeOutCloseToEnemySound) {
		// �{�����[���ɏ�Z����l������������B
		m_closeToEnemySoundMulVolume -= g_gameTime->GetFrameDeltaTime();
		// �ŏ��l�𒴂��Ȃ��悤�ɌŒ肷��B
		if (m_closeToEnemySoundMulVolume <= MIN_SOUND_MUL_VOLUME) {
			m_closeToEnemySoundMulVolume = MIN_SOUND_MUL_VOLUME;
			m_isFadeOutCloseToEnemySound = false;
		}
		return;
	}


	// �������̉������Ă��Ȃ���΁B
	if (m_escapeSound == nullptr) {
		// �t�F�[�h�C��������B
		m_isFadeInCloseToEnemySound = true;
	}
	// ���Ă���΁B
	else {
		// �t�F�[�h�A�E�g������B
		m_isFadeOutCloseToEnemySound = true;
	}
}

void Game::CloseToEnemySoundVolumeControl()
{
	// ��ԋ߂��G�l�~�[�Ƃ̋���������������B
	m_distanceToNearestEnemy = 0.0f;
	// �v���C���[�̍��W�B
	Vector3 playerPos = m_player->GetPosition();

	// �G�l�~�[������
	const auto& enemys = FindGOs<Enemy>("enemy");
	// �G�l�~�[�̐�
	const int size = enemys.size();

	for (int i = 0; i < size; i++) {
		m_enemy = enemys[i];
		// �G�l�~�[�̍��W�B
		Vector3 enemyPos = m_enemy->GetPosition();
		// �G�l�~�[�ƃv���C���[�̋����B
		Vector3 diff = playerPos - enemyPos;
		// ��ԋ߂��G�l�~�[�Ƃ̋����𒲂ׂ�B
		if (m_distanceToNearestEnemy == 0.0f || diff.Length() <= m_distanceToNearestEnemy) {
			m_distanceToNearestEnemy = diff.Length();
		}
	}
	// �{�����[�����v�Z����B
	//m_closeToEnemySoundVolume = MAX_SOUND_VOLUME - (m_distanceToNearestEnemy / CLOSE_TO_ENEMY_SOUND_RANGE * MAX_SOUND_VOLUME);
	
	m_closeToEnemySoundVolume = 0.0f;
	
	// �ŏ����ʖ����ɂȂ�Ȃ��悤�ɌŒ肷��B
	if (m_closeToEnemySoundVolume <= MIN_SOUND_VOLUME) {
		m_closeToEnemySoundVolume = MIN_SOUND_VOLUME;
	}

	// ��Z����l�����߂�B
	FadeCloseToEnemySound();

	// ��Z���ăt�F�[�h��������B
	m_closeToEnemySoundVolume *= m_closeToEnemySoundMulVolume;

	// �{�����[����ݒ�B
	m_closeToEnemySound->SetVolume(m_closeToEnemySoundVolume);
}