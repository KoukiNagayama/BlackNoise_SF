#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start()
{
	// ���f���̏������B
	m_inGameStage.Init(
		"Assets/modelData/stage/2ndFloor/Floor2.tkm",
		nullptr,
		0,
		enModelUpAxisZ,
		0
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
