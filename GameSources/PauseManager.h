/*!
@file PauseManager.h
@brief ポーズマネージャー
*/

#pragma once
#include "stdafx.h"
#include "PauseSprite.h"

namespace basecross {
	//---------------------------------------------------------------------------------------------------------------
	//ポーズマネージャークラス
	//---------------------------------------------------------------------------------------------------------------

	class PauseManager :public GameObject {
		bool m_isPlaying;//動いてるかどうか

		std::vector<std::shared_ptr<PauseSprite>> m_pauseSprites;//ポーズスプライトの変数
		std::shared_ptr<PauseSprite> catPointSprite;//左矢印
		std::shared_ptr<PauseSprite> Pause;
		shared_ptr<SoundItem> m_SE;


		//ポーズフラグ
		int m_SpriteNum;//今選択しているスプライト


		void ChangeSelect(int num);
		//矢印のY軸を変更させる関数
		void SetSelectPosition(int SpriteNum);
		bool m_CntrolLock;
		float m_selectY;//矢印のY座標の位置
		float m_selectX;//矢印のX座標の位置


	public:

		PauseManager(const shared_ptr<Stage>& stage) :
			GameObject(stage),
			m_CntrolLock(false),
			m_isPlaying(true),
			m_SpriteNum(0),
			m_selectX(0.0f),
			m_selectY(0.0f)
		{
		}
		virtual ~PauseManager(){}


		bool IsPlaying() const
		{
			return m_isPlaying;
		}

		void PauseManager::PlayGame(bool isPause)
		{
			//ゲーム実行中のフラグを折る
			m_isPlaying = isPause;

			//「現在のステージ」にあるすべてのゲームオブジェクトを停止させる
			auto stage = GetStage();
			auto gameObjects = stage->GetGameObjectVec();
			for (auto& gameObject : gameObjects)
			{
				if (dynamic_pointer_cast<PauseManager>(gameObject))
				{
					continue;
				}
				gameObject->SetUpdateActive(isPause);


			}

		}
		void PauseManager::PauseGame();

		virtual void OnCreate() override;//初期化
		virtual void OnUpdate() override;//更新
		virtual void OnDraw() override;//描画

		//スプライトナンバーのアクセサ
		int GetSpriteNum() const
		{
			return m_SpriteNum;
		}

		void SetSpriteNum(int i)
		{
			m_SpriteNum = i;
		}

	};
}

