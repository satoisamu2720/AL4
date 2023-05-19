#pragma once
#include "Enemy.h"
#include "VectraCalculation.h"

///
///
/// 
void Enemy::Initialize(Model* model, const Vector3& position) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
};

	
	

///
///
///
void Enemy::Update() {
	worldTransform_.TransferMatrix();
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	worldTransform_.translation_.z -= kCharacterSpeed;

	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
};

///
///
///
void Enemy::Draw(const ViewProjection view){ 
	model_->Draw(worldTransform_, view, textureHandle_); 
};