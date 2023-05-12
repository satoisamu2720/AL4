#include "Player.h"
#include <cassert>




void Player::Initialize(Model* model, uint32_t textureHandle) { 
	assert(model); 
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	//シングルトンインスタンスを無視する
	input_ = Input::GetInstance();

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() { 
	worldTransform_.TransferMatrix(); 

	//キャラ移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラの移動速さ
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

}

void Player::Draw(ViewProjection view) { model_->Draw(worldTransform_, view, textureHandle_); }




