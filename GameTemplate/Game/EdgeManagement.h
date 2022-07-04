#pragma once
class Bell;
class Player;
class Enemy;
class TitleCamera;
class Game;
class EdgeManagement
{
public:
	EdgeManagement() {};
	~EdgeManagement() {};

	/// <summary>
	/// �����������B
	/// </summary>
	void Init();
	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();
	/// <summary>
	/// �N���A�B
	/// </summary>
	void Clear();
	/// <summary>
	/// �֊s������̏����擾�B
	/// </summary>
	/// <returns>�֊s������̏��</returns>
	EdgeControl* GetEdgeControl()
	{
		return &m_edgeControl;
	}
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="number">�����̔ԍ��B</param>
	/// <param name="position">�ݒ肷����W�B</param>
	void SetPosition(int number, Vector3 position) 
	{
		m_edgeControl.SetPosition(number, position);
	}
	/// <summary>
	/// ���������Ă��邩�ǂ�����ݒ�B
	/// </summary>
	/// <param name="number">�����̔ԍ��B</param>
	/// <param name="isSound">���������Ă��邩�B1�͖��Ă���B0�͖��Ă��Ȃ��B</param>
	void SetIsSound(int number, int isSound)
	{
		m_edgeControl.SetIsSound(number, isSound);
	}
	/// <summary>
	/// ���Ԍo�߂ɂ��e������ݒ�B
	/// </summary>
	/// <param name="number">�����̔ԍ��B</param>
	/// <param name="rateByTime">���Ԍo�߂ɂ��e�����B</param>
	void SetRateByTime(int number, float rateByTime)
	{
		m_edgeControl.SetRate(number, rateByTime);
	}
private:
	/// <summary>
	/// ���W���w��B
	/// </summary>
	void SpecifyPosition();
	/// <summary>
	/// ���Ԃɂ��e�������w��B
	/// </summary>
	void SpecifyRateByTime();
	/// <summary>
	/// �������Ă��邩���w��B
	/// </summary>
	void SpecifyIsSound();
	/// <summary>
	/// �x���̉e�������v�Z�B
	/// </summary>
	void CalcRateOfBell();
	/// <summary>
	/// �v���C���[�̑����̉e�������v�Z�B
	/// </summary>
	void CalcRateOfPlayerFootstep();
	/// <summary>
	/// �G�l�~�[�̑����̉e�������v�Z�B
	/// </summary>
	void CalcRateOfEnemyFootstep();
	/// <summary>
	/// �G�l�~�[�̙��K�̉e�������v�Z�B
	/// </summary>
	void CalcRateOfEnemyScream();
	/// <summary>
	/// �x���̉������Ă��邩�w��B
	/// </summary>
	void SpecifyIsBellSounding();
	/// <summary>
	/// �v���C���[�̑��������Ă��邩�w��B
	/// </summary>
	void SpecifyIsPlayerFootstepSounding();
	/// <summary>
	/// �G�l�~�[�̑��������Ă��邩�w��B
	/// </summary>
	void SpecifyIsEnemyFootstepSounding();
	/// <summary>
	/// �G�l�~�[�̑��������Ă��邩�w��B
	/// </summary>
	void SpecifyIsEnemyScreamSounding();
private:
	enum EnSoundSourceData
	{
		enSoundSourceData_Bell,				// �x��
		enSoundSourceData_PlayerFootstep,	// �v���C���[�̑���
		enSoundSourceData_EnemyFootstep,	// �G�l�~�[�̑���
		enSoundSourceData_EnemyScream,		// �G�l�~�[�̙��K
		enSoundSourceData_Title,			// �^�C�g��
		enSoundSourceData_Num				// ���̌�
	};

	enum EnRateByTimeState
	{
		enRateByTimeState_RateUnChanged,	// �e�����ω��Ȃ��B
		enRateByTimeState_RateUp,			// �e�����㏸�B
		enRateByTimeState_RateDown			// �e�������~�B
	};

	EdgeControl				m_edgeControl;											// �֊s������
	Bell*					m_bell = nullptr;										// �x��
	Player*					m_player = nullptr;										// �v���C���[
	Enemy*					m_enemy = nullptr;										// �G�l�~�[
	TitleCamera*			m_titleCamera = nullptr;								// �^�C�g���J����
	float					m_rateByTimeOfBell = 0.0f;								// �x���̎��Ԍo�߂ɂ��e����
	bool					m_isRateUpOfBell = false;								// �x���̉e�������グ�邩
	bool					m_isLastBellSound = false;								// �x���͒��O�͖��Ă����� 
	float					m_rateByTimeOfPlayerFootstep = 0.0f;					// �v���C���[�̑����̎��Ԍo�߂ɂ��e����
	bool					m_isRateUpOfPlayerFootstep = false;						// �v���C���[�̑����̉e�������グ�邩
	bool					m_isLastPlayerFootstepSound = false;					// �v���C���[�̑����͒��O�͖��Ă�����
	float					m_rateByTimeOfEnemyFootstep = 0.0f;						// �G�l�~�[�̑����̎��Ԍo�߂ɂ��e����
	bool					m_isRateUpOfEnemyFootstep = false;						// �G�l�~�[�̑����̉e�������グ�邩
	bool					m_isLastEnemyFootstepSound = false;						// �G�l�~�[�̑����͒��O�͖��Ă�����
	float					m_rateByTimeOfEnemyScream = 0.0f;						// �G�l�~�[�̙��K�̎��Ԍo�߂ɂ��e����
	bool					m_isRateUpOfEnemyScream = false;						// �G�l�~�[�̙��K�̉e�������グ�邩
	bool					m_isLastEnemyScream = false;							// �G�l�~�[�̙��K�͒��O�͖��Ă�����
	Vector3					m_positionOfCenterInTitle = Vector3::Zero;				// �^�C�g���̎��̒��S�̍��W
	Game*					m_game = nullptr;										// �Q�[��
};

