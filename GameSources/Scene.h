/*!
@file Scene.h
@brief シーン
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {

		void CreateResourses();

		bool m_isPlaying;

		//現在セレクトされているステージナンバー
		int m_StageNum;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		
		//Pauseの処理
		Scene() :
			SceneBase(),
			m_isPlaying(true)
		{}

		bool IsPlaying() const
		{
			return m_isPlaying;
		}

		void PlayGame(bool isPause)
		{
			//「ゲーム実行中」フラグを折る
			m_isPlaying = isPause;

			//「現在のステージ」にあるすべてのゲームオブジェクトを停止させる
			auto stage = GetActiveStage();
			auto gameObjects = stage->GetGameObjectVec();
			for (auto& gameObject : gameObjects)
			{
				gameObject->SetUpdateActive(isPause);
			}
		}

		void PauseGame()
		{
			PlayGame(!IsPlaying());
		}

		//ステージナンバーのアクセサ
		int GetStageNum() const
		{
			return m_StageNum;
		}

		void SetStageNum(int i)
		{
			m_StageNum = i;
		}

		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;


	};

}

//end basecross
