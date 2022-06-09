#pragma once
#include "Bloom.h"
namespace nsK2EngineLow {
	class RenderingEngine
	{
	public:
		/// <summary>
		/// �����_�����O�p�C�v���C����������
		/// </summary>
		void Init();
		/// <summary>
		/// �����_�����O�p�C�v���C�������s
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		void Execute(RenderContext& rc);
		/// <summary>
		/// GBuffer�̕`��p�X�Ƀ��f����ǉ�
		/// </summary>
		/// <param name="model"></param>
		void Add3DModelToRenderGBufferPass(Model& model)
		{
			m_renderToGBufferModels.push_back(&model);
		}
		/// <summary>
		/// �t�H���[�h�����_�����O�̕`��p�X�Ƀ��f����ǉ�
		/// </summary>
		/// <param name="model"></param>
		void Add3DModelToForwardRenderPass(Model& model)
		{
			m_forwardRenderModels.push_back(&model);
		}
		/// <summary>
		/// 2D�`��p�X��2D��ǉ�
		/// </summary>
		/// <param name="sprite"></param>
		void Add2DTo2DRenderPass(Sprite& sprite)
		{
			m_sprites.push_back(&sprite);
		}
		/// <summary>
		/// �[�x�l�L�^�p�̃����_�����O�^�[�Q�b�g���擾
		/// </summary>
		/// <returns>�[�x�l�L�^�p�����_�����O�^�[�Q�b�g</returns>
		RenderTarget& GetDepthValue()
		{
			return m_gBuffer[enGBufferDepth];
		}
		/// <summary>
		/// ���[���h���W�L�^�p�̃����_�����O�^�[�Q�b�g���擾
		/// </summary>
		/// <returns>���[���h���W�L�^�p�̃����_�����O�^�[�Q�b�g</returns>
		RenderTarget& GetWorldPos()
		{
			return m_gBuffer[enGBufferWorldPos];
		}
		/// <summary>
		/// �@���L�^�p�̃����_�����O�^�[�Q�b�g���擾
		/// </summary>
		/// <returns>�@���L�^�p�̃����_�����O�^�[�Q�b�g</returns>
		RenderTarget& GetNormal()
		{
			return m_gBuffer[enGBufferNormal];
		}
	private:
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g��������
		/// </summary>
		void InitMainRenderTarget();
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�̓��e���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g��������
		/// </summary>
		void InitCopyMainRenderTargetToFrameBufferSprite();
		/// <summary>
		/// G-Buffer��������
		/// </summary>
		void InitGBuffer();
		/// <summary>
		/// 2D�`��p�����_�����O�^�[�Q�b�g��������
		/// </summary>
		void Init2DRenderTarget();
		/// <summary>
		/// G-Buffer�ւ̕`��
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		void RenderToGBuffer(RenderContext& rc);
		/// <summary>
		/// �t�H���[�h�����_�����O
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		void ForwardRendering(RenderContext& rc);
		/// <summary>
		/// 2D�`��
		/// </summary>
		/// <param name="rc"></param>
		void Render2D(RenderContext& rc);
		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g�̓��e���t���[���o�b�t�@�ɃR�s�[
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);
	private:
		// G-Buffer�̒�`
		enum EnGBuffer
		{
			enGBufferDepth,				// �[�x
			enGBufferNormal,			// �@��
			enGBufferWorldPos,			// ���[���h���W
			enGBufferNum,				// G-Buffer�̐�
		};

		std::vector<Model*>		m_renderToGBufferModels;				// G-Buffer�̕`��p�X�ŕ`�悳��郂�f��
		std::vector<Model*>		m_forwardRenderModels;					// �t�H���[�h�����_�����O�̕`��p�X�ŕ`�悳��郂�f��
		std::vector<Sprite*>	m_sprites;								// �`�悷��X�v���C�g
		RenderTarget			m_mainRenderTarget;						// ���C�������_�����O�^�[�Q�b�g
		RenderTarget			m_gBuffer[enGBufferNum];				// G-Buffer�p�̃����_�����O�^�[�Q�b�g
		RenderTarget			m_2DRenderTarget;						// 2D�`��p�̃����_�����O�^�[�Q�b�g
		Sprite					m_copyMainRtToFrameBufferSprite;		// ���C�������_�����O�^�[�Q�b�g�̓��e���t���[���o�b�t�@�ɃR�s�[����p�̃X�v���C�g
		Sprite					m_2DSprite;								// 2D�����p�X�v���C�g
		Sprite					m_mainSprite;
		Bloom					m_bloom;
	};
	extern RenderingEngine g_renderingEngine;
}


