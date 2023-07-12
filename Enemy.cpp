#pragma once
#include "Enemy.h"
#include "VectraCalculation.h"
 
Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {

		delete bullet;
	}
}

void Enemy::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
};
void Enemy::Atack() {
	if (bullet_) {

	delete bullet_;
	bullet_ = nullptr;
     }
	const float kBulletSpeed = 1.0f;
	Vector3 velcity(0, 0, kBulletSpeed);
	velcity = TransformNormal(velcity, worldTransform_.matWorld_);
	EnemyBullet* newBulllet = new EnemyBullet();
	newBulllet->Initialize(model_, worldTransform_.translation_, velcity);
	// 弾を登録する
	bullets_.push_back(newBulllet);
}


///
///
///
void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	
	const float kCharacterSpeed = 0.2f;
	
	switch (phase_) {
	case Phase::Approach:
	
		
		//移動（ベクトルを加算）
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
		worldTransform_.translation_.z -= kCharacterSpeed;

		break;
	case Phase::Leave:
		
		//移動（ベクトルを加算）
		worldTransform_.translation_ = Add(worldTransform_.translation_, {-0.5f, 0.5f, 0.0f});
		
		break;
	default:
		break;
	}
	

	
};
//void Enemy::Approach
    ///
///
///
void Enemy::Draw(const ViewProjection view){ 
	model_->Draw(worldTransform_, view, textureHandle_); 
};