#pragma once
#include "stdafx.h"

namespace basecross 
{
	class OpeningCamera : public GameObject
	{
		Vec3 m_StartPos;
		Vec3 m_EndPos;
		Vec3 m_AtStartPos;
		Vec3 m_AtEndPos;
		Vec3 m_AtPos;
		float m_TotalTime;
		//ステートマシーン
		unique_ptr< StateMachine<OpeningCamera> >  m_StateMachine;

	public:
		//構築と破棄
		OpeningCamera(const shared_ptr<Stage>& StagePtr);
		virtual ~OpeningCamera();
		//初期化
		virtual void OnCreate() override;
		//操作
		virtual void OnUpdate() override;


	};

}