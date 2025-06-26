/*!
@file Character.cpp
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross 
{
	//--------------------------------------------------------------------------------------
	//　オープニングカメラマン
	//--------------------------------------------------------------------------------------
	//構築と破棄
	OpeningCameraman::OpeningCameraman(const shared_ptr<Stage>& StagePtr) :
		GameObject(StagePtr),
		m_StartPos(-20.0f, 5.0f, -20.0f),//カメラの開始位置
		m_EndPos(18.0f, 2.0f, 10.0f),//カメラの目標終了位置
		m_AtStartPos(0.0f, 0.0f, 0.0f),//カメラの注視点の開始位置
		m_AtEndPos(18.0f, 0.0f, 18.0f),//カメラの目標終了位置
		m_AtPos(m_AtStartPos),//現在のカメラの注視点を開始位置に初期化
		m_TotalTime(0.0f)//このステートでの経過時間をリセット
	{}
	OpeningCameraman::~OpeningCameraman() {}

	//初期化
	void OpeningCameraman::OnCreate() 
	{
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetPosition(m_StartPos);
		ptr->SetRotation(0.0f, 180.0f, 0.0f);
		//ステートマシンの構築
		m_StateMachine.reset(new StateMachine<OpeningCameraman>(GetThis<OpeningCameraman>()));
		//最初のステートをOpeningCameramanToGoalStateに設定
		m_StateMachine->ChangeState(OpeningCameramanToGoalState::Instance());

	}

	//操作
	void OpeningCameraman::OnUpdate() 
	{
		//ステートマシンのUpdateを行う
		//この中でステートの切り替えが行われる
		m_StateMachine->Update();
	}

	// ゴールへ向かうステートに入る時の初期化処理
	void OpeningCameraman::ToGoalEnterBehavior()
	{
		m_StartPos = Vec3(-25.0f, 22.0f, 0.0f);
		m_EndPos = Vec3(40.0f, 20.75f, 0.0f); //ゴールオブジェクト付近
		m_AtStartPos = Vec3(0.0f, 0.0f, 0.0f);
		m_AtEndPos = Vec3(40.0f,20.0f,-10.0f);  //ゴールオブジェクト付近
		m_AtPos = m_AtStartPos; //現在の注視点をリセット
		m_TotalTime = 0.0f;     //経過時間をリセット
	}

	// スタート地点（プレイヤーを見る位置）へ向かうステートに入る時の初期化処理
	void OpeningCameraman::ToStartEnterBehavior()
	{
		m_StartPos = Vec3(40.0f, 20.75f, 0.0f);  // 前のステートの終点が始点 
		m_EndPos = Vec3(0.0f, 3.0f, -5.0f);
		m_AtStartPos = Vec3(40.0f, 20.0f, 0.0f); // 前のステートの注視点終点が始点
		m_AtEndPos = Vec3(-25.0f, 22.0f, -0.5f);     // プレイヤーの初期位置を見る
		m_AtPos = m_AtStartPos;                  // 現在の注視点をリセット
		m_TotalTime = 0.0f;                      // 経過時間をリセット
	}

	// カメラの補間移動を実行する関数 (指定された総時間 `totaltime` で移動完了を目指す)
	bool OpeningCameraman::ExcuteBehavior(float totaltime)
	{
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime; // このステートでの総経過時間を加算
		if (m_TotalTime > totaltime) // 総経過時間が目標時間を超えたら、移動完了として true を返す
		{
			return true;
		}
		Easing<Vec3> easing;
		// カメラの目標位置 (TgtPos) を、始点(m_StartPos)から終点(m_EndPos)へ、 現在の経過時間(m_TotalTime)と総時間(totaltime)に基づいてイージング補間して計算
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		// カメラの注視点 (m_AtPos) も同様にイージング補間で計算
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime); 
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos); // 計算した新しいカメラ位置を設定
		return false; // まだ目標時間に達していなければ false を返す (移動は継続)
	}

	// オープニングの最終ステートに入った時の処理
	void OpeningCameraman::EndStateEnterBehavior() 
	{
		auto ptrGameGtage = GetTypeStage<GameStage>();
		ptrGameGtage->ToPhase1Camera(); // GameStageのToMyCamera()関数を呼び出し、カメラをPhase1Cameraに切り替える
	}


	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	// このステートの唯一のインスタンスを取得する静的関数
	shared_ptr<OpeningCameramanToGoalState> OpeningCameramanToGoalState::Instance() 
	{
		static shared_ptr<OpeningCameramanToGoalState> instance(new OpeningCameramanToGoalState);
		return instance;
	}

	// このステートに入った時に呼ばれる関数
	void OpeningCameramanToGoalState::Enter(const shared_ptr<OpeningCameraman>& Obj) 
	{
		// OpeningCameramanオブジェクトに、ゴールへ向かうための初期設定を行わせる
		Obj->ToGoalEnterBehavior();
	}

	// このステート実行中に毎フレーム呼ばれる関数
	void OpeningCameramanToGoalState::Execute(const shared_ptr<OpeningCameraman>& Obj)
	{
		// OpeningCameramanに補間移動を実行させる (目標時間5.0秒)
		if (Obj->ExcuteBehavior(5.0f))
		{
			//次のステート (OpeningCameramanToStartState: プレイヤーを見る位置へ移動) に遷移する
			Obj->GetStateMachine()->ChangeState(OpeningCameramanToStartState::Instance());
		}
	}

	// このステートから出る時に呼ばれる関数
	void OpeningCameramanToGoalState::Exit(const shared_ptr<OpeningCameraman>& Obj)
	{
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToStartState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToStartState> OpeningCameramanToStartState::Instance()
	{
		static shared_ptr<OpeningCameramanToStartState> instance(new OpeningCameramanToStartState);
		return instance;
	}
	void OpeningCameramanToStartState::Enter(const shared_ptr<OpeningCameraman>& Obj)
	{
		// OpeningCameramanオブジェクトに、スタート位置（プレイヤーを見る位置）へ向かうための初期設定を行わせる
		Obj->ToStartEnterBehavior();
	}
	void OpeningCameramanToStartState::Execute(const shared_ptr<OpeningCameraman>& Obj) 
	{
		// OpeningCameramanに補間移動を実行させる (目標時間3.0秒)
		if (Obj->ExcuteBehavior(3.0f)) 
		{
			// 次のステート (OpeningCameramanEndState: オープニング終了) に遷移する
			Obj->GetStateMachine()->ChangeState(OpeningCameramanEndState::Instance());
		}
	}
	void OpeningCameramanToStartState::Exit(const shared_ptr<OpeningCameraman>& Obj) 
	{
	}

	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanEndState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanEndState> OpeningCameramanEndState::Instance() 
	{
		static shared_ptr<OpeningCameramanEndState> instance(new OpeningCameramanEndState);
		return instance;
	}

	void OpeningCameramanEndState::Enter(const shared_ptr<OpeningCameraman>& Obj) 
	{
		// OpeningCameramanオブジェクトに、オープニング終了時の処理（カメラ切り替えなど）を行わせる
		Obj->EndStateEnterBehavior();
	}

	// このステートでは特に毎フレーム行う処理はない
	void OpeningCameramanEndState::Execute(const shared_ptr<OpeningCameraman>& Obj)
	{
	}

	void OpeningCameramanEndState::Exit(const shared_ptr<OpeningCameraman>& Obj)
	{
	}




}
//end basecross
