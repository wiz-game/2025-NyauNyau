#pragma once
#include "stdafx.h"

namespace basecross
{

	class Phase1 : public GameObject 
	{

		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::shared_ptr<GameObject> boxObject;
		std::shared_ptr<Player> player;

		//入力ハンドラー
		InputHandler<Player> m_InputHandler;

		Vec2 GetInputState() const;
		bool m_Phase1;
		bool m_CollisionEnabled;
		bool isFrozen = true; // 初期状態で動作停止


	public:
		//構築と破棄
		Phase1(const shared_ptr<Stage>& StagePtr
		);

		void Initialize();
		//void SetCollisionEnabled(bool enabled);



		virtual ~Phase1() {}
		//アクセサ
		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;

	};


}