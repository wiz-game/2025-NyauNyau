#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//構築と破棄
	Phase1::Phase1(const shared_ptr<Stage>& StagePtr
	) :
		GameObject(StagePtr),
		m_Phase1(true),
		m_CollisionEnabled(true)
	{
		// 初期化
		//gameObjects = {}; // 空のリストとして初期化
		//boxObject = nullptr; // 初期状態でnull
	}


	Vec2 Phase1::GetInputState() const {
		Vec2 ret;
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		ret.x = 0.0f;
		ret.y = 0.0f;
		WORD wButtons = 0;

		return ret;
	}


    void Phase1::OnCreate()
    {

    }
    
    void Phase1::OnUpdate()
    {
    	//コントローラの取得
    	auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
    
    	// Bボタンの入力
    	if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
    	{
    		for (auto& obj : gameObjects)
    		{
                isFrozen = false;

    		}
    	}

        // isFrozen が true の間は何も動かせない
        if (isFrozen) return;

        auto playertransform = player->GetComponent<Transform>();
        // 通常のオブジェクト更新処理
        //for (auto& obj : GetStage()->GetThis<GameStage>()->GetGameObjectVec()) 
        //{
        //    obj->;
        //}


    }
    
    
    void Phase1::Initialize()
    {
        isFrozen = true; // ステージ開始時はすべてのオブジェクトを停止
        
    }
    
    void SetCollisionEnabled(bool enabled)
    {
    	//m_CollisionEnabled = enabled;
    }
}