#pragma once
namespace nsK2EngineLow {
	class Bloom
	{
	public:
		Bloom() {};
		~Bloom() {};

		/// <summary>
		/// �u���[�����s�ɕK�v�ȑS�Ă̗v�f�̏�����
		/// </summary>
		/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
		void Init(RenderTarget& mainRenderTarget);
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);
	private:
		/// <summary>
		/// �P�x���o�p�̃����_�����O�^�[�Q�b�g��������
		/// </summary>
		/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
		void InitLuminanceRenderTarget(RenderTarget& mainRenderTarget);
		/// <summary>
		/// �P�x���o�p�̃X�v���C�g��������
		/// </summary>
		/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
		void InitSprite(RenderTarget& mainRenderTarget);
		/// <summary>
		/// �K�E�V�A���u���[��������
		/// </summary>
		void InitBlur();
		/// <summary>
		/// �{�P�摜�����Z��������X�v���C�g��������
		/// </summary>
		/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
		void InitFinalSprite(RenderTarget& mainRenderTarget);
	private:
		RenderTarget		m_luminanceRenderTarget;			// �P�x���o�p�̃����_�����O�^�[�Q�b�g
		GaussianBlur		m_gaussianBlur[4];					// �K�E�V�A���u���[
		Sprite				m_luminanceSprite;					// �P�x���o�p�̃X�v���C�g
		Sprite				m_finalSprite;						// �{�P�摜�����Z��������X�v���C�g
	};
}


