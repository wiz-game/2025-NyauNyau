/*!
@file MainCamera.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"


namespace basecross {

	//初期化
	void MainCamera::OnCreate()
	{
	}

	// 更新処理
	void MainCamera::OnUpdate()
	{
		// weak_ptrをロックして、オブジェクトが存在しなければ終了する
		auto targetObj = m_targetObj.lock();
		if (!targetObj)
		{
			return;
		}

		auto& app = App::GetApp(); // アプリケーションオブジェクトを取得

		float delta = app->GetElapsedTime(); // 経過時間を取得

		// ゲームパッドオブジェクトを取得
		auto& device = app->GetInputDevice();
		auto& pad = device.GetControlerVec()[0]; // 0番目を選択

		// オブジェクトに追従するようにする
		auto trans = targetObj->GetComponent<Transform>();
		auto targetPos = trans->GetPosition();

		m_height += pad.fThumbRY * delta;

		m_height -= 10.0f * pad.fThumbRY * delta;
		m_angleY -= XMConvertToRadians(150.0f) * pad.fThumbRX * delta; // 右スティックの傾きに応じて、秒間最大135°回り込む

		Vec3 at = targetPos + Vec3(0.0f, 1.0f, 0.0f);
		Vec3 eye = targetPos + Vec3(cosf(m_angleY) * m_distance, m_height, sinf(m_angleY) * m_distance);

		SetAt(at);
		SetEye(eye);

		// ターゲットオブジェクトがプレイヤーだったら、アングルを伝える
		auto player = dynamic_pointer_cast<Player>(targetObj);
		if (player)
		{
			player->SetCameraAngleY(m_angleY);
		}
	}
}
//end basecross
