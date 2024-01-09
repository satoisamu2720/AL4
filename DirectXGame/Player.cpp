#pragma once
#include "Player.h"
#include "VectraCalculation.h"

Player::~Player() {}

void Player::Initialize(
    const std::vector<Model*>& models) {
	BaseCharacter::Initialize(models);
	
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	worldTransformHammer_.Initialize();

	worldTransform_.translation_ = playerPosition;
	worldTransformBody_.translation_ = bodyPosition;
	worldTransformHead_.translation_ = headPosition;
	worldTransformL_arm_.translation_ = l_amrPosition;
	worldTransformR_arm_.translation_ = r_amrPosition;
	worldTransformHammer_.translation_ = hammerPosition;


	worldTransformL_arm_.rotation_.x = 0.5f;
	worldTransformR_arm_.rotation_.x = 0.5f;


	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformHead_.parent_ = &worldTransform_;
	worldTransformL_arm_.parent_ = &worldTransform_;
	worldTransformR_arm_.parent_ = &worldTransform_;
	worldTransformHammer_.parent_ = &worldTransform_;
	//worldTransformHead_.translation_ = {0.0f, 0.2f, 0.0f};

	input_ = Input::GetInstance();

	worldTransform_.translation_ = Add(worldTransform_.translation_, playerPosition);
	InitializeFloatingGimmick();
};

void Player::Update() {
	BehaviorRootUpdate();
	// worldTransform_.TransferMatrix();

	Vector3 move_ = {0, 0, 0};

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.5f;
	// const float kRotSpeed = 0.05f;
	if (input_->PushKey(DIK_W)) {
		move_.z += kCharacterSpeed;
	} else if (input_->PushKey(DIK_S)) {
		move_.z -= kCharacterSpeed;
	}
	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_A)) {
		move_.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_D)) {
		move_.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_SPACE)){
		
	}

	// worldTransformHead_.translation_.y = 5;

	UpdateFloatingGimmick();

	move_ = TransformNormal(move_, MakeRotateYMatrix(viewProjection_->rotation_.y));
	// Y軸周り角度
	worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move_);
	// 行列更新
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	worldTransformHammer_.UpdateMatrix();

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

	//// 移動限界座標
	// const float kMoveLimitX = 34;
	// const float kMoveLimitY = 18;

	//// 範囲を超えない処理
	// worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	// worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	// worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	// worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
}

void Player::Draw(ViewProjection view) {

	models_[0]->Draw(worldTransformBody_, view);
	models_[1]->Draw(worldTransformHead_, view);
	models_[2]->Draw(worldTransformL_arm_, view);
	models_[3]->Draw(worldTransformR_arm_, view);
	models_[4]->Draw(worldTransformHammer_, view);
}
void Player::OnCollision() {}

Vector3 Player::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::InitializeFloatingGimmick() { floatingParameter_ = 1.0f; }

void Player::UpdateFloatingGimmick() {
	const uint16_t period = 120;
	const float step = 2.0f * (float)M_PI / period;

	floatingParameter_ += step;
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * (float)M_PI);

	const float amplitude = 0.02f;
	worldTransform_.translation_.y += std::sin(floatingParameter_) * amplitude;
	//worldTransformHead_.translation_.y = std::sin(floatingParameter_) * amplitude;
	worldTransformL_arm_.rotation_.x+= std::cos(floatingParameter_) * amplitude;
	worldTransformR_arm_.rotation_.x += std::cos(floatingParameter_) * amplitude;
}
void Player::DrawFloatingGimmick() {}


void Player::BehaviorRootUpdate(){}
