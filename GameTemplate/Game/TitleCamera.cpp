#include "stdafx.h"
#include "TitleCamera.h"
#include "TitleText.h"

namespace
{
	const float NEAR_CLIP = 3.0f;					//�j�A�[�N���b�v
	const float FAR_CLIP = 10000.0f;				//�t�@�[�N���b�v
}

bool TitleCamera::Start()
{
	m_tText = FindGO<TitleText>("titleText");
	Vector3	target = m_tText->GetPosition();
	// �J�����̏����ݒ�
	// �J�����̋ߕ��ʂƉ����ʂ�ݒ�
	g_camera3D->SetNear(NEAR_CLIP);
	g_camera3D->SetFar(FAR_CLIP);

	// �����_��ݒ�B
	g_camera3D->SetTarget(target);

	// ���_��ݒ�B
	g_camera3D->SetPosition(m_cameraPos);

	return true;
}

void TitleCamera::Update()
{
	// �J�������X�V����B
	g_camera3D->Update();
}


