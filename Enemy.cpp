#pragma once
#include "Enemy.h"
#include "VectraCalculation.h"
 
Enemy::~Enemy() {
	for (EnemyBullet* enemybullet : enemybullets_) {

		delete enemybullet;
		delete enemybullet_;
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
void Enemy::Fire() {
	enemybullet_ = nullptr;

	const float kBulletSpeed = -0.4f;
	Vector3 velcity(0, 0, kBulletSpeed);
	velcity = TransformNormal(velcity, worldTransform_.matWorld_);
	EnemyBullet* newBulllet = new EnemyBullet();
	newBulllet->Initialize(model_, worldTransform_.translation_, velcity);
	// 弾を登録する
	enemybullets_.push_back(newBulllet);
	
		
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
	
	Fire();
	if (enemybullet_) {
		enemybullet_->Updarte();
	}
	for (EnemyBullet* bullet : enemybullets_) {
		bullet->Updarte();
	}
	
};

void Enemy::Draw(const ViewProjection view){ 
	model_->Draw(worldTransform_, view, textureHandle_); 
	for (EnemyBullet* bullet : enemybullets_) {
		bullet->Draw(view);
	}
};