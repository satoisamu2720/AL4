#pragma once
#include "Player.h"
#include "VectraCalculation.h"

Player::~Player() {

}


void Player::Initialize(Model* model ,Vector3 position) {

	assert(model);
	model_ = model;
	
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	input_ = Input::GetInstance();
	worldTransform_.translation_ = Add(worldTransform_.translation_, position);
};

void Player::Update() {
	

	worldTransform_.TransferMatrix();
	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;
	const float kRotSpeed = 0.2f;
	if (input_->PushKey(DIK_A)) {
	  worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
	  worldTransform_.rotation_.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
	  move.z += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
	  move.z -= kCharacterSpeed;
	}
	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
	  move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
	  move.x += kCharacterSpeed;
	}

	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_W)) {
	  move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_S)) {
	  move.y -= kCharacterSpeed;
	}

	// ベクターの加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列更新
	worldTransform_.UpdateMatrix();



	float imputFloat3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	// デバッグ
	ImGui::Begin("Debug");
	ImGui::Text("Toggle Camera Flag :  LEFT SHIFT key");
	ImGui::SliderFloat3("player", imputFloat3, -30.0f, 30.0f);
	ImGui::End();
	worldTransform_.translation_.x = imputFloat3[0];
	worldTransform_.translation_.y = imputFloat3[1];
	worldTransform_.translation_.z = imputFloat3[2];

	// 移動限界座標
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	
}

void Player::Draw(ViewProjection view) { 

	model_->Draw(worldTransform_, view);

};

void Player::OnCollision() {  }


Vector3 Player::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return  worldPos;
}
	
