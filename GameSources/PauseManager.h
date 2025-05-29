/*!
@file PauseManager.h
@brief ポーズマネージャー
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//---------------------------------------------------------------------------------------------------------------
	//ポーズマネージャークラス
	//---------------------------------------------------------------------------------------------------------------

	class PauseManager :public GameObject {
		bool m_isPlaying;//動いてるかどうか

		std::vector<std::weak_ptr<PauseSprite>> m_pauseSprites;//ポーズスプライトの変数
		std::shared_ptr<PauseSprite> catPointSprite;//左矢印
		std::shared_ptr<PauseSprite> Pause;

		//ポーズフラグ
		//bool m_PauseFlag = false;
		bool m_pauseSprite = false;
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
			m_isPlaying(true)
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
				gameObject->SetUpdateActive(isPause);
			}

		}

		void PauseManager::PauseGame();

		virtual void OnCreate() override;//初期化
		virtual void OnUpdate() override;//更新


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

