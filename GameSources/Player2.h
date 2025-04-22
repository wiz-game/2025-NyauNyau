
/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross
{
	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject {
		//プレイヤーが使用するコントローラの入力
		Vec2 GetInputState() const;
		// コントローラから方向ベクトルを得る
		Vec3 GetMoveVector() const;
		//プレイヤーの移動
		void MovePlayer();

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;


		//入力ハンドラー
		InputHandler<Player> m_InputHandler;
		//スピード
		float m_Speed;

		bool m_Player1;
		//空中にいるか
		bool m_isAir;

		float m_cameraAngleY; // カメラの回り込み
		float m_velocityY;
		Vec3 m_forward; // 前方向を示すベクトル
		Vec3 m_velocity;
		bool m_collisionFlag;
		const float m_gravity;
		void DrawStrings();

	public:
		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr,
			Vec3& m_Scale,
		    Vec3& m_Rotation,
			Vec3& m_Position
		);

		void SetPlayerMove(bool Player1);


		virtual ~Player() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		
		//Aボタン
		void OnPushA();

	};
}
//end basecross

