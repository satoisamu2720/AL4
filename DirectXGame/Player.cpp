#pragma once
#include "Player.h"
#include "VectraCalculation.h"

Player::~Player() {}

void Player::Initialize(
    const std::vector<Model*>& models) {
	BaseCharacter::Initialize(models);
	//初期化
	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	worldTransformHammer_.Initialize();

	//初期ポジティブ
	worldTransform_.translation_ = playerPosition;
	worldTransformBody_.translation_ = bodyPosition;
	worldTransformHead_.translation_ = headPosition;
	worldTransformL_arm_.translation_ = l_amrPosition;
	worldTransformR_arm_.translation_ = r_amrPosition;
	worldTransformHammer_.translation_ = hammerPosition;

	//親子関係
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

	if (behaviorRequest_) {
		//振るまいを変更する
		behavior_ = behaviorRequest_.value();
		//各振るまいごとの初期化を実行
		switch (behavior_) {
		case Player::Behavior::kRoot:
		default:
			BehaviorRootInitialize();
			break;
		case Player::Behavior::kAttack:
			BehaviorAttackInitialize();
			break;
		}
		//振るまいリクエストをリセット
		behaviorRequest_ = std::nullopt;
	}
	
	switch (behavior_) {
	case Player::Behavior::kRoot :
	default:
		BehaviorRootUpdate();
		break;
	case Player::Behavior::kAttack:
			BehaviorAttackUpdate();
		break;
	}

	// 行列更新
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();
	worldTransformHammer_.UpdateMatrix();

	
	float imputFloatR_arm[3] = {
	    worldTransformR_arm_.rotation_.x, worldTransformR_arm_.rotation_.y,
	    worldTransformR_arm_.rotation_.z
	};
	float imputFloatHammerR[3] = {
	    worldTransformHammer_.rotation_.x, worldTransformHammer_.rotation_.y,
	    worldTransformHammer_.rotation_.z};

	float imputFloatHammer[3] = {
	    worldTransformHammer_.translation_.x, worldTransformHammer_.translation_.y,
	    worldTransformHammer_.translation_.z};

	float inputAttackTime = attackTime;

	// デバッグ
	ImGui::Begin("Debug");
	ImGui::Text("Toggle Camera Flag :  LEFT SHIFT key");
	ImGui::SliderFloat3("player", imputFloatR_arm, -3.0f, 0.0f);
	ImGui::SliderFloat3("HammerR", imputFloatHammerR, 0.0f, 3.0f);
	ImGui::SliderFloat3("Hammer", imputFloatHammer, -3.0f, 3.0f);
	ImGui::InputFloat("AttackTime", &inputAttackTime);
	ImGui::Checkbox(" AttackFlag \n false = Right \n true = Left", &attackFlag);
	ImGui::End();
	worldTransformR_arm_.rotation_.x = imputFloatR_arm[0];
	worldTransformR_arm_.rotation_.y = imputFloatR_arm[1];
	worldTransformR_arm_.rotation_.z = imputFloatR_arm[2];

	worldTransformHammer_.rotation_.x = imputFloatHammerR[0];
	worldTransformHammer_.rotation_.y = imputFloatHammerR[1];
	worldTransformHammer_.rotation_.z = imputFloatHammerR[2];
	worldTransformHammer_.translation_.x = imputFloatHammer[0];
	worldTransformHammer_.translation_.y = imputFloatHammer[1];
	worldTransformHammer_.translation_.z = imputFloatHammer[2];
	attackTime = inputAttackTime;

}

void Player::Draw(ViewProjection view) {

	models_[0]->Draw(worldTransformBody_, view);
	models_[1]->Draw(worldTransformHead_, view);
	models_[2]->Draw(worldTransformL_arm_, view);
	models_[3]->Draw(worldTransformR_arm_, view);
	if (attackFlag == false) {
		if (behavior_ == Behavior::kAttack) {
			models_[4]->Draw(worldTransformHammer_, view);
		} 
	} else {
		models_[4]->Draw(worldTransformHammer_, view);
	}
}
void Player::OnCollision() {}

Vector3 Player::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::InitializeFloatingGimmick() { floatingRootParameter_ = 1.0f; }

void Player::BehaviorRootInitialize() {
	worldTransform_.translation_.y = 0.0f;
	worldTransformL_arm_.rotation_.x = 0.0f;
	worldTransformR_arm_.rotation_.x = 0.0f;
	worldTransformL_arm_.rotation_.y = 0.0f;
	worldTransformR_arm_.rotation_.y = 0.0f;
	 floatingRootParameter_ = 0.0f;
	
}
void Player::UpdateFloatingGimmick() {
	const uint16_t period = 120;
	const float step = 2.0f * (float)M_PI / period;

	floatingRootParameter_ += step;
	floatingRootParameter_ = std::fmod(floatingRootParameter_, 2.0f * (float)M_PI);

	//const float amplitude = 0.02f;
	//worldTransform_.translation_.y += std::sin(floatingRootParameter_) * amplitude;
	//worldTransformHead_.translation_.y = std::sin(floatingParameter_) * amplitude;
	/*worldTransformL_arm_.rotation_.x += std::cos(floatingRootParameter_) * amplitude;
	worldTransformR_arm_.rotation_.x += std::cos(floatingRootParameter_) * amplitude;*/
}
void Player::DrawFloatingGimmick() {
	
}


void Player::BehaviorRootUpdate(){
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
	if (input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kAttack;
	}
	// worldTransformHead_.translation_.y = 5;
	move_ = TransformNormal(move_, MakeRotateYMatrix(viewProjection_->rotation_.y));
	// Y軸周り角度
	worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move_); 
	UpdateFloatingGimmick();
}
void Player::BehaviorAttackInitialize() {

	worldTransformHammer_.rotation_.x = 1.5f;
	worldTransformHammer_.rotation_.z = 1.55f;

	worldTransformR_arm_.rotation_.x = -1.5f;
	worldTransformR_arm_.rotation_.y = 0.0f;

	floatingAttackParameter_ = 0.0f;
}
void Player::BehaviorAttackUpdate() { 
	const uint16_t attackPeriod = 60;
	attackTime++;
	const float attackStep = 1.0f * (float)M_PI / attackPeriod;

	floatingAttackParameter_ += attackStep;
	floatingAttackParameter_ = std::fmod(floatingAttackParameter_, 1.0f * (float)M_PI);

	// const float amplitude = 0.5f;
	const float armAmplitude = 0.08f;
	const float hammerAmplitude = 0.08f;

	//worldTransformL_arm_.rotation_.x -= std::cos(floatingAttackParameter_) * armAmplitude;
	worldTransformR_arm_.rotation_.y -= std::cos(floatingAttackParameter_) * armAmplitude;
	worldTransformHammer_.rotation_.x -= std::cos(floatingAttackParameter_) * hammerAmplitude;

	if (attackTime >= 90) {
		behaviorRequest_ = Player::Behavior::kRoot;
		attackTime = 0;
	}
}
