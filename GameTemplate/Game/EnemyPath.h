#pragma once
#include "LevelRender.h"

/// <summary>
/// �p�X�ړ��̃|�C���g���
/// </summary>
struct Point {
	Vector3 s_position;				// �|�C���g�̍��W
	int     s_number;				// �|�C���g�̔ԍ�
};

/// <summary>
/// �G�l�~�[�p�X�N���X
/// </summary>
class  EnemyPath
{
public:
	/// <summary>
	/// �p�X�ړ��̍ŏ��̃|�C���g�����擾
	/// </summary>
	/// <returns>�p�X�ړ��̍ŏ��̃|�C���g���</returns>
	Point* GetFirstPoint()
	{
		return &m_pointlist[0];
	}
	/// <summary>
	/// �p�X�ړ��̎��̃|�C���g�����擾
	/// </summary>
	/// <param name="number">���ݒn�̃|�C���g�̔ԍ�</param>
	/// <returns>�p�X�ړ��̎��̃|�C���g���</returns>
	Point* GetNextPoint(const int number)
	{
		return &m_pointlist[number + 1];
	}
	/// <summary>
	/// �p�X�ړ��p�̃|�C���g�̐����擾
	/// </summary>
	/// <returns>�p�X�ړ��p�̃|�C���g�̐�</returns>
	int GetPointListSize()
	{
		return m_pointlist.size();
	}
	/// <summary>
	/// ���݂̍��W�����ԋ߂��|�C���g���擾
	/// </summary>
	/// <param name="position">���W</param>
	/// <returns>�|�C���g</returns>
	Point* GetNearPoint(const Vector3& position);
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="filePath">�|�C���g�o�^�Ɏg�p�������x���̃t�@�C���p�X</param>
	void Init(const char* filePath);
private:
	Point* m_point;					// �|�C���g�\����
	std::map<int, Point>		m_pointlist;				// �p�X�ړ��p�̃|�C���g���X�g
	LevelRender					m_level;					// ���x�������_�[
};

