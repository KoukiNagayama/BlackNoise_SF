#include "stdafx.h"
#include "BackGround.h"
#include "EdgeManagement.h"

namespace
{
	const int EDGE_COLOR_WHITE = 0;					// �֊s���̐F
	const int NUM_ANIMATIONCLIP = 0;				// �A�j���[�V�����N���b�v�̐�
	const int MAX_INSTANCE = 0;						// �C���X�^���X�̍ő吔
}

BackGround::~BackGround()
{
	m_physicsStaticObject.Release();
}

bool BackGround::Start()
{
	// ���f���̏������B
	m_inGameStage.Init(
		"Assets/modelData/stage/2ndFloor/Floor2.tkm",
		nullptr,
		NUM_ANIMATIONCLIP,
		enModelUpAxisZ,
		MAX_INSTANCE,
		EDGE_COLOR_WHITE,
		m_edgeManagement->GetEdgeControl()
	);

	// ���f������ÓI�����I�u�W�F�N�g�𐶐��B
	m_physicsStaticObject.CreateFromModel(
		m_inGameStage.GetModel(),
		m_inGameStage.GetModel().GetWorldMatrix()
	);

	return true;
}

void BackGround::Update()
{
	// ���f���̍X�V�B
	m_inGameStage.Update();
}

void BackGround::Render(RenderContext& rc)
{
	// ���f���̕`��B
	m_inGameStage.Draw();
}
