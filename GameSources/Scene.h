/*!
@file Scene.h
@brief �V�[��
*/
#pragma once

#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase {
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase() {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		//AddObject�̒ǉ�
		std::vector<shared_ptr<ObjectInterface>> m_addObjects;

		void AddObject(shared_ptr<ObjectInterface> obj)
		{
			m_addObjects.push_back(obj);
		};


		//RemoveObject�̒ǉ�
		std::vector<shared_ptr<ObjectInterface>> m_removeObjects;

		void RemoveObject(shared_ptr<ObjectInterface> obj) {
			auto it = std::find(m_removeObjects.begin(), m_removeObjects.end(), obj);
			if (it != m_removeObjects.end()) {
				m_removeObjects.erase(it);
			}
		}
	};

}

//end basecross
