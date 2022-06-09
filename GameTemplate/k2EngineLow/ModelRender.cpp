#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		int outlineType
	)
	{
		// �X�P���g�����������B
		InitSkeleton(filePath);
		// �A�j���[�V�������������B
		InitAnimation(animationClips, numAnimationClips);
		// �t�H���[�h�����_�����O�p�̃��f�����������B
		InitForwardRenderingModel(filePath, enModelUpAxis, outlineType);
		// GBuffer�`��p�̃��f����������
		InitModelOnRenderToGBuffer(filePath, enModelUpAxis);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips,
		int numAnimationClips)
	{
		m_numAnimationClips = numAnimationClips;
		m_animationClips = animationClips;

		if (m_animationClips != nullptr) {
			// �A�j���[�V������������
			m_animation.Init(
				m_skeleton,					// �A�j���[�V�����𗬂����ރX�P���g��
				m_animationClips,			// �A�j���[�V�����N���b�v
				m_numAnimationClips			// �A�j���[�V�����̐�
			);
		}
	}

	void ModelRender::InitForwardRenderingModel(const char* filePath,
		EnModelUpAxis enModelUpAxis,
		int outlineType
	)
	{
		ModelInitData modelInitData;
		// tkm�t�@�C���̃t�@�C���p�X���w�肷��B
		modelInitData.m_tkmFilePath = filePath;
		// �V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��B
		modelInitData.m_fxFilePath = "Assets/shader/test.fx";
		/*if (outlineType == 0) {
			modelInitData.m_fxFilePath = "Assets/shader/edge.fx";
		}
		else if (outlineType == 1) {
			modelInitData.m_fxFilePath = "Assets/shader/edgeFRorange.fx";
		}
		else if (outlineType == 2) {
			modelInitData.m_fxFilePath = "Assets/shader/edgeFRred.fx";
		}
		else if (outlineType == 3) {
			modelInitData.m_fxFilePath = "Assets/shader/edgeTitleText.fx";
		}
		else if (outlineType == 4) {
			modelInitData.m_fxFilePath = "Assets/shader/whiteBoard.fx";
		}*/

		// �G���g���[�|�C���g���w�肷��B
		if (m_animationClips != nullptr) {
			//�X�P���g�����w�肷��B
			modelInitData.m_skeleton = &m_skeleton;
			//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}
		// �J���[�o�b�t�@�̃t�H�[�}�b�g���w�肷��B
		modelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;
		// �e��}�b�v���g��SRV�ɐݒ肷��B
		modelInitData.m_expandShaderResoruceView[0] = &g_renderingEngine.GetDepthValue().GetRenderTargetTexture();
		modelInitData.m_expandShaderResoruceView[1] = &g_renderingEngine.GetWorldPos().GetRenderTargetTexture();
		modelInitData.m_expandShaderResoruceView[2] = &g_renderingEngine.GetNormal().GetRenderTargetTexture();
		
		// ���f���̏�������w�肷��B
		modelInitData.m_modelUpAxis = enModelUpAxis;
		// �����f�[�^��萔�o�b�t�@�Ƃ��Đݒ肷��
		//modelInitData.m_expandConstantBuffer = (void*)&g_infoForEdge.GetSoundSourceData();
		//modelInitData.m_expandConstantBufferSize = sizeof(g_infoForEdge.GetSoundSourceData());
		// �쐬�����������f�[�^�����ƂɃ��f��������������B
		m_forwardRenderModel.Init(modelInitData);
	}

	void ModelRender::InitModelOnRenderToGBuffer(const char* filePath,
		EnModelUpAxis enModelUpAxis
	)
	{
		ModelInitData modelInitData;
		// ���f���̏�������w�肷��
		modelInitData.m_modelUpAxis = enModelUpAxis;
		// �V�F�[�_�[�t�@�C���̃t�@�C���p�X���w�肷��
		modelInitData.m_fxFilePath = "Assets/shader/RenderToGBufferFor3DModel.fx";
		// �G���g���[�|�C���g���w�肷��B
		if (m_animationClips != nullptr) {
			//�X�P���g�����w�肷��B
			modelInitData.m_skeleton = &m_skeleton;
			//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
			modelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else {
			//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
			modelInitData.m_vsEntryPointFunc = "VSMain";
		}
		// tkm�t�@�C���̃t�@�C���p�X���w�肷��
		modelInitData.m_tkmFilePath = filePath;
		// �������f�[�^�����ƂɃ��f����������
		m_renderToGBufferModel.Init(modelInitData);
	}

	void ModelRender::Update()
	{

		UpdateWorldMatrix();

		if (m_skeleton.IsInited()) {
			// �X�P���g�����X�V
			m_skeleton.Update(m_forwardRenderModel.GetWorldMatrix());
		}
		
		// �A�j���[�V�������X�V
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::UpdateWorldMatrix()
	{
		if (m_renderToGBufferModel.IsInited())
		{
			m_renderToGBufferModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		}
		if (m_forwardRenderModel.IsInited())
		{
			m_forwardRenderModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		}
	}

	void ModelRender::Draw()
	{
		if (m_renderToGBufferModel.IsInited())
		{
			g_renderingEngine.Add3DModelToRenderGBufferPass(m_renderToGBufferModel);
		}
		if (m_forwardRenderModel.IsInited())
		{
			g_renderingEngine.Add3DModelToForwardRenderPass(m_forwardRenderModel);
		}
	}
}
