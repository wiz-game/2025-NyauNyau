
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
		void MoveToWallPosition(const shared_ptr<GameObject>& wall);
		//void GetPlayer(shared_ptr<GameObject>& Player);

		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;


		//入力ハンドラー
		InputHandler<Player> m_InputHandler;
		//スピード
		float m_Speed;
		float m_Player1;
		//空中にいるか
		bool m_isAir;

	public:
		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr,
			Vec3& m_Scale,
		    Vec3& m_Rotation,
			Vec3& m_Position
		);

		virtual void SetPlayerMove(bool Player1);


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

