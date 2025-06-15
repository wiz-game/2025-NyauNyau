#pragma once
/*!
@file Ground.h
@brief キャラクターなど
*/
#include "stdafx.h"


namespace basecross {

	//ステージに追加可能な地面を表すクラス
	class Table : public GameObject
	{
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;

		shared_ptr<PNTStaticModelDraw> m_drawComp;


	public:
		Table (const shared_ptr<Stage>& stage,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position
		);

		virtual ~Table();


		void OnCreate() override; // 初期設定用のイベントハンドラ
		void OnUpdate() override;

		void InitDrawComp();

	};
}
//end basecross
