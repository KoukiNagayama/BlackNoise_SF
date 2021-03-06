#pragma once
#include "Bloom.h"
#include "EdgeControl.h"
namespace nsK2EngineLow {

	const int MAX_TEXT_SIZE = 256;

	struct SFont
	{
		wchar_t s_text[MAX_TEXT_SIZE];
		Vector3 s_position = Vector3::Zero;
		Vector4 s_color = Vector4::White;
		Vector2 s_pivot = Sprite::DEFAULT_PIVOT;
		float	s_rotation = 0.0f;
		float   s_scale = 1.0f;
	};


	class RenderingEngine
	{
	public:
		/// <summary>
		/// レンダリングパイプラインを初期化
		/// </summary>
		void Init();
		/// <summary>
		/// レンダリングパイプラインを実行
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		void Execute(RenderContext& rc);
		/// <summary>
		/// GBufferの描画パスにモデルを追加
		/// </summary>
		/// <param name="model"></param>
		void Add3DModelToRenderGBufferPass(Model& model)
		{
			m_renderToGBufferModels.push_back(&model);
		}
		/// <summary>
		/// フォワードレンダリングの描画パスにモデルを追加
		/// </summary>
		/// <param name="model"></param>
		void Add3DModelToForwardRenderPass(Model& model)
		{
			m_forwardRenderModels.push_back(&model);
		}
		/// <summary>
		/// スプライト描画パスにスプライトを追加
		/// </summary>
		/// <param name="sprite"></param>
		void AddSpriteToSpriteRenderPass(Sprite& sprite)
		{
			m_sprites.push_back(&sprite);
		}
		/// <summary>
		/// フォント描画パスにフォントを追加
		/// </summary>
		/// <param name="font"></param>
		void AddFontToFontRenderPass(Font& font)
		{
			m_fonts.push_back(&font);
		}
		/// <summary>
		/// 深度値記録用のレンダリングターゲットを取得
		/// </summary>
		/// <returns>深度値記録用レンダリングターゲット</returns>
		RenderTarget& GetDepthValue()
		{
			return m_gBuffer[enGBufferDepth];
		}
		/// <summary>
		/// ワールド座標記録用のレンダリングターゲットを取得
		/// </summary>
		/// <returns>ワールド座標記録用のレンダリングターゲット</returns>
		RenderTarget& GetWorldPos()
		{
			return m_gBuffer[enGBufferWorldPos];
		}
		/// <summary>
		/// 法線記録用のレンダリングターゲットを取得
		/// </summary>
		/// <returns>法線記録用のレンダリングターゲット</returns>
		RenderTarget& GetNormal()
		{
			return m_gBuffer[enGBufferNormal];
		}
	private:
		/// <summary>
		/// メインレンダリングターゲットを初期化
		/// </summary>
		void InitMainRenderTarget();
		/// <summary>
		/// メインレンダリングターゲットのカラーバッファの内容をフレームバッファにコピーするためのスプライトを初期化
		/// </summary>
		void InitCopyMainRenderTargetToFrameBufferSprite();
		/// <summary>
		/// G-Bufferを初期化
		/// </summary>
		void InitGBuffer();
		/// <summary>
		/// 2D描画用レンダリングターゲットを初期化
		/// </summary>
		void Init2DRenderTarget();
		/// <summary>
		/// G-Bufferへの描画
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		void RenderToGBuffer(RenderContext& rc);
		/// <summary>
		/// フォワードレンダリング
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		void ForwardRendering(RenderContext& rc);
		/// <summary>
		/// スプライト描画
		/// </summary>
		/// <param name="rc"></param>
		void RenderSprite(RenderContext& rc);
		/// <summary>
		/// フォント描画
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		void RenderFont(RenderContext& rc);
		/// <summary>
		/// メインレンダリングターゲットの内容をフレームバッファにコピー
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		void CopyMainRenderTargetToFrameBuffer(RenderContext& rc);
	private:
		// G-Bufferの定義
		enum EnGBuffer
		{
			enGBufferDepth,				// 深度
			enGBufferNormal,			// 法線
			enGBufferWorldPos,			// ワールド座標
			enGBufferNum,				// G-Bufferの数
		};

		std::vector<Model*>		m_renderToGBufferModels;				// G-Bufferの描画パスで描画されるモデル
		std::vector<Model*>		m_forwardRenderModels;					// フォワードレンダリングの描画パスで描画されるモデル
		std::vector<Sprite*>	m_sprites;								// スプライトの描画パスで描画するスプライト
		std::vector<Font*>		m_fonts;								// フォントの描画パスで描画するフォント
		std::vector<SFont*>		m_sfonts;								// フォントの描画に必要な情報
		RenderTarget			m_mainRenderTarget;						// メインレンダリングターゲット
		RenderTarget			m_gBuffer[enGBufferNum];				// G-Buffer用のレンダリングターゲット
		RenderTarget			m_2DRenderTarget;						// 2D描画用のレンダリングターゲット
		Sprite					m_copyMainRtToFrameBufferSprite;		// メインレンダリングターゲットの内容をフレームバッファにコピーする用のスプライト
		Sprite					m_2DSprite;								// 2D合成用スプライト
		Sprite					m_mainSprite;
		Bloom					m_bloom;
		EdgeControl				m_edgeControl;
	};
	extern RenderingEngine g_renderingEngine;
}
 

