#include "stdafx.h"
#include "EdgeManagement.h"
#include "Bell.h"
#include "Player.h"
#include "Enemy.h"
#include "TitleCamera.h"
#include "Game.h"
namespace
{
	const float BELL_RANGE = 2000.0f;					// �x�����֊s���ɉe����^����͈�
	const float PLAYER_FOOTSTEP_RANGE = 300.0f;			// �v���C���[�̑������֊s���ɉe����^����͈�
	const float ENEMY_FOOTSTEP_RANGE = 450.0f;			// �G�l�~�[�̑������֊s���ɉe����^����͈�
	const float ENEMY_SCREAM_RANGE = 1300.0f;			// �G�l�~�[�̙��K���֊s���ɉe����^����͈�
	const float TITLE_RANGE = 800.0f;					// �^�C�g���ŗ֊s���ɉe����^����͈�
	const float TITLE_OUTLINE_RATE = 1.0f;				// �^�C�g���ł̗֊s���̉e����

	const int IS_SOUND = 1;								// �������Ă���
	const int IS_NOT_SOUND = 0;							// �������Ă��Ȃ�
	const float EDGE_FADE_IN_DELTA_VALUE = 0.05f;		// �G�b�W���t�F�[�h�C������Ƃ��̕ψʗ�
	const float EDGE_FADE_OUT_DELTA_VALUE = 0.00f;	// �G�b�W���t�F�[�h�A�E�g����Ƃ��̕ψʗ�
	const float RATE_BY_TIME_MAX_VALUE = 1.00f;			// ���Ԃɂ��e�����̍ő�l
	const float RATE_BY_TIME_MIN_VALUE = 0.00f;			// ���Ԃɂ��e�����̍ŏ��l
}

void EdgeManagement::Init()
{
	m_game = FindGO<Game>("game");
	// �x���̃C���X�^���X�������B
	m_bell = FindGO<Bell>("bell");
	// �v���C���[�̃C���X�^���X�������B
	m_player = FindGO<Player>("player");
	// �G�l�~�[�̃C���X�^���X�������B
	m_enemy = FindGO<Enemy>("enemy");
	



	// �x���̗֊s���ւ̉e�����������B
	m_edgeControl.Init(
		enSoundSourceData_Bell,
		Vector3::Zero,
		BELL_RANGE,
		m_rateByTimeOfBell
	);
	m_edgeControl.SetIsSound(enSoundSourceData_Bell, IS_NOT_SOUND);


	// �v���C���[�̑����̗֊s���ւ̉e�����������B
	m_edgeControl.Init(
		enSoundSourceData_PlayerFootstep,
		Vector3::Zero,
		PLAYER_FOOTSTEP_RANGE,
		m_rateByTimeOfPlayerFootstep
	);
	m_edgeControl.SetIsSound(enSoundSourceData_PlayerFootstep, IS_NOT_SOUND);


	// �G�l�~�[�̑����̗֊s���ւ̉e�����������B
	m_edgeControl.Init(
		enSoundSourceData_EnemyFootstep,
		Vector3::Zero,
		ENEMY_FOOTSTEP_RANGE,
		m_rateByTimeOfEnemyFootstep
	);
	m_edgeControl.SetIsSound(enSoundSourceData_EnemyFootstep, IS_NOT_SOUND);


	// �G�l�~�[�̙��K�̗֊s���ւ̉e�����������B
	m_edgeControl.Init(
		enSoundSourceData_EnemyScream,
		Vector3::Zero,
		ENEMY_SCREAM_RANGE,
		m_rateByTimeOfEnemyScream
	);
	m_edgeControl.SetIsSound(enSoundSourceData_EnemyScream, IS_NOT_SOUND);

	// �^�C�g���̎��́B
	if (m_game->IsTitle()) {
		// �^�C�g���J�����̏����擾����B
		m_titleCamera = FindGO<TitleCamera>("titleCamera");
		// �֊s���`��̒��S���^�C�g���J�����̍��W�Ƃ���B
		m_positionOfCenterInTitle = m_titleCamera->GetPosition();
	}

	// �^�C�g���̎��̗֊s���ւ̉e�����������B
	m_edgeControl.Init(
		enSoundSourceData_Title,
		m_positionOfCenterInTitle,
		TITLE_RANGE,
		TITLE_OUTLINE_RATE
	);
	m_edgeControl.SetIsSound(enSoundSourceData_Title, IS_NOT_SOUND);
}

void EdgeManagement::Update()
{
	if (m_bell == nullptr || m_player == nullptr || m_enemy == nullptr) {
		return;
	}

	// �������Ă��邩���w��B
	SpecifyIsSound();

	if (m_game->IsInGame() == false) {
		return;
	}

	// ���W���w��B
	SpecifyPosition();

	// ���Ԃɂ��e�������w��B
	SpecifyRateByTime();


}

void EdgeManagement::Clear()
{
	// �o�^���̃N���A�B
	m_edgeControl.Clear();
}

void EdgeManagement::SpecifyPosition()
{
	// �x���B
	m_edgeControl.SetPosition(enSoundSourceData_Bell, m_bell->GetPosition());

	// �v���C���[�̑����B
	m_edgeControl.SetPosition(enSoundSourceData_PlayerFootstep, m_player->GetPosition());

	// �G�l�~�[�̑����B
	m_edgeControl.SetPosition(enSoundSourceData_EnemyFootstep, m_enemy->GetPosition());

	// �G�l�~�[�̙��K�B
	m_edgeControl.SetPosition(enSoundSourceData_EnemyScream, m_enemy->GetPosition());
}

void EdgeManagement::SpecifyIsSound()
{
	if (m_game->IsTitle()) {
		m_edgeControl.SetIsSound(enSoundSourceData_Title, IS_SOUND);
		return;
	}
	
	// �x���B
	SpecifyIsBellSounding();

	// �v���C���[�̑����B
	SpecifyIsPlayerFootstepSounding();

	// �G�l�~�[�̑����B
	SpecifyIsEnemyFootstepSounding();

	// �G�l�~�[�̙��K�B
	SpecifyIsEnemyScreamSounding();
}

void EdgeManagement::SpecifyIsBellSounding()
{
	// ���Ă��鎞�B
	if (m_bell->IsBellRinging() == true && m_isLastBellSound == false) {
		m_edgeControl.SetIsSound(enSoundSourceData_Bell, IS_SOUND);
		m_isLastBellSound = true;
	}
	// ���Ă��Ȃ����B
	else if (m_bell->IsBellRinging() == false && m_isLastBellSound == true) {
		m_edgeControl.SetIsSound(enSoundSourceData_Bell, IS_NOT_SOUND);
	}
}

void EdgeManagement::SpecifyIsPlayerFootstepSounding()
{
	// ���Ă��鎞�B
	if (m_player->IsPlayerFootstepSound() == true && m_isLastPlayerFootstepSound == false) {
		m_edgeControl.SetIsSound(enSoundSourceData_PlayerFootstep, IS_SOUND);
		m_isLastPlayerFootstepSound = true;
	}
	// ���Ă��Ȃ����B
	else if (m_player->IsPlayerFootstepSound() == false && m_isLastPlayerFootstepSound == true) {
		m_edgeControl.SetIsSound(enSoundSourceData_PlayerFootstep, IS_NOT_SOUND);
		m_isLastPlayerFootstepSound = false;
	}
}

void EdgeManagement::SpecifyIsEnemyFootstepSounding()
{
	// ���Ă��鎞�B
	if (m_enemy->IsMoving() == true && m_isLastEnemyFootstepSound == false) {
		m_edgeControl.SetIsSound(enSoundSourceData_EnemyFootstep, IS_SOUND);
		m_isLastEnemyFootstepSound = true;
	}
	// ���Ă��Ȃ����B
	else if (m_enemy->IsMoving() == false && m_isLastEnemyFootstepSound == true) {
		m_edgeControl.SetIsSound(enSoundSourceData_EnemyFootstep, IS_NOT_SOUND);
		m_isLastEnemyFootstepSound = false;
	}
}

void EdgeManagement::SpecifyIsEnemyScreamSounding()
{
	// ���Ă��鎞�B
	if (m_enemy->IsScream() == true && m_isLastEnemyScream == false) {
		m_edgeControl.SetIsSound(enSoundSourceData_EnemyScream, IS_SOUND);
		m_isLastEnemyScream = true;
	}
	// ���Ă��Ȃ����B
	else if (m_enemy->IsScream() == false && m_isLastEnemyScream == true) {
		m_edgeControl.SetIsSound(enSoundSourceData_EnemyScream, IS_NOT_SOUND);
		m_isLastEnemyScream = false;
	}
}

void EdgeManagement::SpecifyRateByTime()
{
	// �x���B
	CalcRateOfBell();
	// �v���C���[�̑����B
	CalcRateOfPlayerFootstep();
	// �G�l�~�[�̑����B
	CalcRateOfEnemyFootstep();
	// �G�l�~�[�̙��K�B
	CalcRateOfEnemyScream();
}

void EdgeManagement::CalcRateOfBell()
{
	// �x�������Ă���Ȃ�΁B
	if (m_bell->IsBellRinging()) {
		// �x���̉e�������グ��悤�ɂ���B
		m_isRateUpOfBell = true;
	}
	// �x���̉e�������グ��悤�ɂȂ��Ă���Ȃ�΁B
	if (m_isRateUpOfBell) {
		// �e�������ő�l�����ł���΁B
		if (m_rateByTimeOfBell < RATE_BY_TIME_MAX_VALUE) {
			// �e�������グ��B
			m_rateByTimeOfBell += EDGE_FADE_IN_DELTA_VALUE;
		}
		// �e�������ő�l�𒴂��Ă���Ȃ�΁B
		else {
			// �e�������グ�Ȃ��悤�ɂ���B
			m_isRateUpOfBell = false;
		}
	}
	// �x���̉e������0���傫���Ȃ��
	else if (m_rateByTimeOfBell > RATE_BY_TIME_MIN_VALUE) {
		// �e������������B
		m_rateByTimeOfBell -= EDGE_FADE_OUT_DELTA_VALUE;
		if (m_rateByTimeOfBell < RATE_BY_TIME_MIN_VALUE) {
			m_rateByTimeOfBell = RATE_BY_TIME_MIN_VALUE;
		}
	}
	// �x���̉e������ݒ�B
	m_edgeControl.SetRate(enSoundSourceData_Bell, m_rateByTimeOfBell);
}

void EdgeManagement::CalcRateOfPlayerFootstep()
{
	// �v���C���[�̑��������Ă���Ȃ�΁B
	if (m_player->IsPlayerFootstepSound()) {
		// �v���C���[�̑����̉e�������グ��悤�ɂ���B
		m_isRateUpOfPlayerFootstep = true;
	}
	// �v���C���[�̑������グ��悤�ɂȂ��Ă���Ȃ�΁B
	if (m_isRateUpOfPlayerFootstep) {
		// �e�������ő�l�����ł���΁B
		if (m_rateByTimeOfPlayerFootstep < RATE_BY_TIME_MAX_VALUE) {
			// �e�������グ��B
			m_rateByTimeOfPlayerFootstep += EDGE_FADE_IN_DELTA_VALUE;
		}
		// �e�������ő�l�𒴂��Ă���Ȃ�΁B
		else {
			// �e�������グ�Ȃ��悤�ɂ���B
			m_isRateUpOfPlayerFootstep = false;
		}
	}
	// �v���C���[�̑����̉e������0���傫���Ȃ��
	else if (m_rateByTimeOfPlayerFootstep > RATE_BY_TIME_MIN_VALUE) {
		// �e������������B
		m_rateByTimeOfPlayerFootstep -= EDGE_FADE_OUT_DELTA_VALUE;
		if (m_rateByTimeOfPlayerFootstep < RATE_BY_TIME_MIN_VALUE) {
			m_rateByTimeOfPlayerFootstep = RATE_BY_TIME_MIN_VALUE;
		}
	}
	// �v���C���[�̑����̉e������ݒ�B
	m_edgeControl.SetRate(enSoundSourceData_PlayerFootstep, m_rateByTimeOfPlayerFootstep);
}

void EdgeManagement::CalcRateOfEnemyFootstep()
{
	// �v���C���[�̑��������Ă���Ȃ�΁B
	if (m_enemy->IsMoving()) {
		// �v���C���[�̑����̉e�������グ��悤�ɂ���B
		m_isRateUpOfEnemyFootstep = true;
	}
	// �v���C���[�̑������グ��悤�ɂȂ��Ă���Ȃ�΁B
	if (m_isRateUpOfEnemyFootstep) {
		// �e�������ő�l�����ł���΁B
		if (m_rateByTimeOfEnemyFootstep < RATE_BY_TIME_MAX_VALUE) {
			// �e�������グ��B
			m_rateByTimeOfEnemyFootstep += EDGE_FADE_IN_DELTA_VALUE;
		}
		// �e�������ő�l�𒴂��Ă���Ȃ�΁B
		else {
			// �e�������グ�Ȃ��悤�ɂ���B
			m_isRateUpOfEnemyFootstep = false;
		}
	}
	// �v���C���[�̑����̉e������0���傫���Ȃ��
	else if (m_rateByTimeOfEnemyFootstep > RATE_BY_TIME_MIN_VALUE) {
		// �e������������B
		m_rateByTimeOfEnemyFootstep -= EDGE_FADE_OUT_DELTA_VALUE;
		if (m_rateByTimeOfEnemyFootstep < RATE_BY_TIME_MIN_VALUE) {
			m_rateByTimeOfEnemyFootstep = RATE_BY_TIME_MIN_VALUE;
		}
	}
	// �v���C���[�̑����̉e������ݒ�B
	m_edgeControl.SetRate(enSoundSourceData_EnemyFootstep, m_rateByTimeOfEnemyFootstep);
}

void EdgeManagement::CalcRateOfEnemyScream()
{
	// �v���C���[�̑��������Ă���Ȃ�΁B
	if (m_enemy->IsScream()) {
		// �v���C���[�̑����̉e�������グ��悤�ɂ���B
		m_isRateUpOfEnemyScream = true;
	}
	// �v���C���[�̑������グ��悤�ɂȂ��Ă���Ȃ�΁B
	if (m_isRateUpOfEnemyScream) {
		// �e�������ő�l�����ł���΁B
		if (m_rateByTimeOfEnemyScream < RATE_BY_TIME_MAX_VALUE) {
			// �e�������グ��B
			m_rateByTimeOfEnemyScream += EDGE_FADE_IN_DELTA_VALUE;
		}
		// �e�������ő�l�𒴂��Ă���Ȃ�΁B
		else {
			// �e�������グ�Ȃ��悤�ɂ���B
			m_isRateUpOfEnemyScream = false;
		}
	}
	// �v���C���[�̑����̉e������0���傫���Ȃ��
	else if (m_rateByTimeOfEnemyScream > RATE_BY_TIME_MIN_VALUE) {
		// �e������������B
		m_rateByTimeOfEnemyScream -= EDGE_FADE_OUT_DELTA_VALUE;
		if (m_rateByTimeOfEnemyScream < RATE_BY_TIME_MIN_VALUE) {
			m_rateByTimeOfEnemyScream = RATE_BY_TIME_MIN_VALUE;
		}
	}
	// �v���C���[�̑����̉e������ݒ�B
	m_edgeControl.SetRate(enSoundSourceData_EnemyScream, m_rateByTimeOfEnemyScream);
}