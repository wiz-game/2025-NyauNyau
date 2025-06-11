
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
		Vec3 m_Scale;
		Vec3 m_Rotation;
		Vec3 m_Position;
		Col4 m_color;
		std::vector<VertexPositionColorTexture> m_vertices;
		std::vector<uint16_t> m_indices;

		int m_number;
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
	
		void MoveY();
		void MoveXZ();
		void OnCollisionExcute(shared_ptr<GameObject>& Other);
		void OnCollisionExit(shared_ptr<GameObject>& Other);
		void Jump(shared_ptr<GameObject>& jump);
	    void DrawStrings();

		shared_ptr<PNTStaticDraw> m_drawComp; // 標準的なアニメーション無しのドローコンポーネント

		// BaseCross上で必要な自身の情報
		shared_ptr<Transform> m_Transform;

		// 自身の情報
		Vec3 m_Center;
		float m_Radius;

		// 衝突相手の情報
		shared_ptr<ShadowObject> m_OtherPolygon;

	

	public:
		//構築と破棄
		Player(const shared_ptr<Stage>& StagePtr,
			Vec3& m_Scale,
		    Vec3& m_Rotation,
			Vec3& m_Position
		);

		void SetPlayerMove(bool Player1);

		//Aボタン
		void OnPushA();



		// カメラの回り込みを設定する
		void SetCameraAngleY(float angleY)
		{
			m_cameraAngleY = angleY;
		}


		void SetCenter(const Vec3& center)
		{
			m_Center = center;
		}

		Vec3 GetCenter() const
		{
			return m_Center;
		}

		//プレイヤーの移動
		void MovePlayer();

		//Vec2 GetNormal(const Vec2& a, const Vec2& b)
		//{
		//	Vec2 edge = Vec2(b.x - a.x, b.y - a.y);
		//	return Vec2(-edge.y, edge.x).normalize();
		//}
		
		// ベクトルの法線（直線の分離軸）を取得
		Vec3 GetNormal(const Vec3& a, const Vec3& b)
		{
			Vec2 edge = Vec2(b.x - a.x, b.y - a.y);
			return Vec3(-edge.y, edge.x,0.0f).normalize();

		}

		// 多角形を分離軸に投影して範囲を取得
		void ProjectOntoAxis(const vector<Vec3>& poly, const Vec3& axis, float& min, float& max)
		{
			min = max = poly[0].dot(axis);
			for (const auto& p : poly)
			{
				float proj = p.dot(axis);
				if (proj < min) min = proj;
				if (proj > max) max = proj;
			}
		}

		// 円を分離軸に投影して範囲を取得
		void ProjectCircleOntoAxis(const Vec3& center, float radius, const Vec3& axis, float& min, float& max)
		{
			float centerProj = center.dot(axis);
			min = centerProj - radius;
			max = (centerProj + radius) * 10;
		}


		// 円と凸多角形の最小押し出しベクトル（MTV）を求める
		bool ComputeMTV(const std::vector<Vec3>& polygonVertices, Vec3& mtv);
		//bool ComputeMTV(const shared_ptr<ShadowObject>& polygon, const Vec3& sphereWorldCenter, float sphereRadius, Vec3& mtv); // 変更後


		virtual ~Player() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

		//void OnCollisionEnter(shared_ptr<GameObject>& collision) override;




	};
}
//end basecross

