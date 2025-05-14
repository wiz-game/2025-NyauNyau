#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	//�\�z�Ɣj��
	Phase1::Phase1(const shared_ptr<Stage>& StagePtr
	) :
		GameObject(StagePtr),
		m_Phase1(true),
		m_CollisionEnabled(true)
	{
		// ������
		//gameObjects = {}; // ��̃��X�g�Ƃ��ď�����
		//boxObject = nullptr; // ������Ԃ�null
	}


	Vec2 Phase1::GetInputState() const {
		Vec2 ret;
		//�R���g���[���̎擾
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
    	//�R���g���[���̎擾
    	auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
    
    	// B�{�^���̓���
    	if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
    	{
    		for (auto& obj : gameObjects)
    		{
                isFrozen = false;

    		}
    	}

        // isFrozen �� true �̊Ԃ͉����������Ȃ�
        if (isFrozen) return;

        auto playertransform = player->GetComponent<Transform>();
        // �ʏ�̃I�u�W�F�N�g�X�V����
        //for (auto& obj : GetStage()->GetThis<GameStage>()->GetGameObjectVec()) 
        //{
        //    obj->;
        //}


    }
    
    
    void Phase1::Initialize()
    {
        isFrozen = true; // �X�e�[�W�J�n���͂��ׂẴI�u�W�F�N�g���~
        
    }
    
    void SetCollisionEnabled(bool enabled)
    {
    	//m_CollisionEnabled = enabled;
    }
}