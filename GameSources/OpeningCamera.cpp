/*!
@file Character.cpp
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
		m_StartPos(-20.0f, 5.0f, -20.0f),
		m_EndPos(18.0f, 2.0f, 10.0f),
		m_AtStartPos(0.0f, 0.0f, 0.0f),
		m_AtEndPos(18.0f, 0.0f, 18.0f),
		m_AtPos(m_AtStartPos),
		m_TotalTime(0.0f)
	{}
	OpeningCameraman::~OpeningCameraman() {}

	//初期化
	void OpeningCameraman::OnCreate() 
	{
		//初期位置などの設定
		auto ptr = GetComponent<Transform>();
		ptr->SetScale(0.25f, 0.25f, 0.25f);	//直径25センチの球体
		ptr->SetRotation(0.0f, 0.0f, 0.0f);
		ptr->SetPosition(m_StartPos);
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

	void OpeningCameraman::ToGoalEnterBehavior()
	{
		m_StartPos = Vec3(-20.0f, 10.0f, -20.0f);
		m_EndPos = Vec3(18.0f, 2.0f, 10.0f);
		m_AtStartPos = Vec3(-10.0f, 0.0f, 0.0f);
		m_AtEndPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	void OpeningCameraman::ToStartEnterBehavior()
	{
		m_StartPos = Vec3(18.0f, 2.0f, 10.0f);
		m_EndPos = Vec3(0.0f, 3.0f, -5.0f);
		m_AtStartPos = Vec3(18.0f, 0.0f, 18.0f);
		m_AtEndPos = Vec3(0.0f, 0.0f, 0.0f);
		m_AtPos = m_AtStartPos;
		m_TotalTime = 0.0f;
	}

	bool OpeningCameraman::ExcuteBehavior(float totaltime)
	{
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		m_TotalTime += ElapsedTime;
		if (m_TotalTime > totaltime)
		{
			return true;
		}
		Easing<Vec3> easing;
		auto TgtPos = easing.EaseInOut(EasingType::Cubic, m_StartPos, m_EndPos, m_TotalTime, totaltime);
		m_AtPos = easing.EaseInOut(EasingType::Cubic, m_AtStartPos, m_AtEndPos, m_TotalTime, totaltime);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetPosition(TgtPos);
		return false;
	}

	void OpeningCameraman::EndStateEnterBehavior() 
	{
		auto ptrGameGtage = GetTypeStage<GameStage>();
		ptrGameGtage->ToMainCamera();
	}




	//--------------------------------------------------------------------------------------
	//	class OpeningCameramanToGoalState : public ObjState<OpeningCameraman>;
	//--------------------------------------------------------------------------------------
	shared_ptr<OpeningCameramanToGoalState> OpeningCameramanToGoalState::Instance() 
	{
		static shared_ptr<OpeningCameramanToGoalState> instance(new OpeningCameramanToGoalState);
		return instance;
	}
	void OpeningCameramanToGoalState::Enter(const shared_ptr<OpeningCameraman>& Obj) 
	{
		Obj->ToGoalEnterBehavior();
	}
	void OpeningCameramanToGoalState::Execute(const shared_ptr<OpeningCameraman>& Obj)
	{
		if (Obj->ExcuteBehavior(5.0f))
		{
			Obj->GetStateMachine()->ChangeState(OpeningCameramanToStartState::Instance());
		}
	}
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
		Obj->ToStartEnterBehavior();
	}
	void OpeningCameramanToStartState::Execute(const shared_ptr<OpeningCameraman>& Obj) 
	{
		if (Obj->ExcuteBehavior(3.0f)) {
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
		Obj->EndStateEnterBehavior();
	}
	void OpeningCameramanEndState::Execute(const shared_ptr<OpeningCameraman>& Obj)
	{
	}
	void OpeningCameramanEndState::Exit(const shared_ptr<OpeningCameraman>& Obj)
	{
	}




}
//end basecross
