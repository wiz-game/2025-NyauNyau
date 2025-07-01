/*!
@file CatWalkSprite.h
@brief 猫の牙のスプライト
*/


#pragma once
#include "stdafx.h"
namespace basecross {
	//----------------------------------------------------------------------------------------------------
	//class TuskCatSprite : public GameObject;
	//----------------------------------------------------------------------------------------------------

	class TuskCatSprite : public GameObject
	{
		Col4 m_color;
		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;
		std::shared_ptr<PCTSpriteDraw> m_drawComp;
		std::shared_ptr<Transform> m_transComp;

		float m_cat;//現在のコマ番号
		float m_isAnimating;//アニメーション中かどうかのフラグ
		float m_animationTime;//アニメーションの経過時間

		const int m_totalFrames;//全ゴマ数
		const float m_frameDuration;//一コマの表示時間


	public:
		//構築と破棄
		TuskCatSprite(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_color(1, 1, 1, 1),
			m_cat(0),
			m_animationTime(0.0f),
			m_isAnimating(false),
			m_totalFrames(11),
			m_frameDuration(0.1f)
		{
		}

		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void SetTuskNum(int number);
		void StartAnimation();//アニメーションを開始する
		void StopAnimation();//アニメーションを止める

		bool IsTuskCatAnimation()
		{
			return m_isAnimating;
		}

	};
}