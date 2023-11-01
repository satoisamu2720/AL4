#pragma once
#include "Player.h"
#include "VectraCalculation.h"

Player::~Player() {

}


void Player::Initialize(
    Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm,
    Vector3 BodyPosition, Vector3 HeadPosition, Vector3 L_armPosition,Vector3 R_armPosition) {	

	assert(modelBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);

	modelFighterBody_ = modelBody;
	modelFighterHead_ = modelHead;
	modelFighterL_arm_ = modelL_arm;
	modelFighterR_arm_ = modelR_arm;

	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	worldTransformBody_.translation_ = BodyPosition;
	worldTransformHead_.translation_ = HeadPosition;
	worldTransformL_arm_.translation_ = L_armPosition;
	worldTransformR_arm_.translation_ = R_armPosition;

	input_ = Input::GetInstance();
	worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, BodyPosition);
	worldTransformHead_.translation_ = Add(worldTransformHead_.translation_, HeadPosition);
	worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, L_armPosition);
	worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, R_armPosition);
	
};

void Player::Update() {
	
	
	//worldTransform_.TransferMatrix();
	
	Vector3 move_ = {0, 0, 0};

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.5f;
	//const float kRotSpeed = 0.05f;
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


	

	move_ = TransformNormal(move_, MakeRotateYMatrix(viewProjection_->rotation_.y));
	// Y軸周り角度
	worldTransformBody_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, move_);
	// 行列更新
	worldTransformBody_.UpdateMatrix();


	// Y軸周り角度
	worldTransformHead_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformHead_.translation_ = Add(worldTransformHead_.translation_, move_);
	// 行列更新
	worldTransformHead_.UpdateMatrix();


	// Y軸周り角度
	worldTransformL_arm_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, move_);
	// 行列更新
	worldTransformL_arm_.UpdateMatrix();


	// Y軸周り角度
	worldTransformR_arm_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, move_);
	// 行列更新
	worldTransformR_arm_.UpdateMatrix();

	


	/*float imputFloat3[3] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z};*/

	// デバッグ
	/*ImGui::Begin("Debug");
	ImGui::Text("Toggle Camera Flag :  LEFT SHIFT key");
	ImGui::SliderFloat3("player", imputFloat3, -30.0f, 30.0f);
	ImGui::End();*/
	//worldTransform_.rotation_.x = imputFloat3[0];
	//worldTransform_.rotation_.y = imputFloat3[1];
	//worldTransform_.rotation_.z = imputFloat3[2];

	//// 移動限界座標
	//const float kMoveLimitX = 34;
	//const float kMoveLimitY = 18;

	//// 範囲を超えない処理
	//worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	//worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	//worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	//worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	
}

void Player::Draw(ViewProjection view) { 

	modelFighterBody_->Draw(worldTransformBody_, view);
	modelFighterHead_->Draw(worldTransformHead_, view);
	modelFighterL_arm_->Draw(worldTransformL_arm_, view);
	modelFighterR_arm_->Draw(worldTransformR_arm_, view);
};
void Player::OnCollision() {  }


Vector3 Player::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return  worldPos;
}
	
