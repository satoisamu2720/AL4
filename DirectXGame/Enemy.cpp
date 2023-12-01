#pragma once
#include "Enemy.h"
#include "Player.h"
#include "VectraCalculation.h"

Enemy::~Enemy() {
	
	
}
void Enemy::Initialize(const std::vector<Model*>& models) {

	BaseCharacter::Initialize(models);	 

	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	worldTransform_.translation_ = enemyPosition;
	worldTransformBody_.translation_ = bodyPosition;
	worldTransformL_arm_.translation_ = l_amrPosition;
	worldTransformR_arm_.translation_ = r_amrPosition;

	

	worldTransformBody_.parent_ = &worldTransform_;
	worldTransformL_arm_.parent_ = &worldTransform_;
	worldTransformR_arm_.parent_ = &worldTransform_;

	
};

void Enemy::Update() {
	Vector3 move_ = {0, 0, 0};


	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

	const float kCharacterSpeed = 0.5f;

	move_.z += kCharacterSpeed; 

	move_ = TransformNormal(move_, MakeRotateYMatrix(viewProjection_->rotation_.y));
	// Y軸周り角度
	worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	// 移動（ベクトルを加算）
	worldTransform_.translation_ = Add(worldTransform_.translation_, move_);
	worldTransform_.rotation_.y += 0.5f;
};

void Enemy::Draw(const ViewProjection viewProjection) {
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformL_arm_, viewProjection);
	models_[2]->Draw(worldTransformR_arm_, viewProjection);
};

void Enemy::OnCollision() {}


Vector3 Enemy::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}