#pragma once
#include "Enemy.h"
#include "Player.h"
#include "VectraCalculation.h"

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {

		delete bullet;
	}
	
}
void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("Enemy.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	
};

void Enemy::Fire() {
	// 弾を生成し，初期化
	

	const float kBulletSpeed = 1.0f;
	Vector3 playerPos = player_->GetWorldPosition();
	Vector3 enemyPos = this->GetWorldPosition();
    Vector3 velcity = Subtract(playerPos, enemyPos);
	velcity = Normalise(velcity);
	velcity.x *= kBulletSpeed;
	velcity.y *= kBulletSpeed;
	velcity.z *= kBulletSpeed;

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velcity);

	// 弾を登録する
	bullets_.push_back(newBullet);
}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	const float kCharacterSpeed = 0.1f;
	// 移動（ベクトルを加算）
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	worldTransform_.translation_.z -= kCharacterSpeed;
	startTimer--;
	if (startTimer <= 5) {

		Fire();
		Approach();

		startTimer = kFreInterval;
	}
	for (EnemyBullet* bullet : bullets_) {
		bullet->Updarte();
	}
};
void Enemy::Approach() { startTimer = 0; }

void Enemy::Draw(const ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
};

Vector3 Enemy::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}