#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	assert(model);

	// テクスチャ読み込み
	texturehandle_ = TextureManager::Load("klee.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = velocity;
};

void EnemyBullet::Updated() {

	worldTransform_.UpdateMatrix();

	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;
	
	if (--deathTime_ <= 0) {
		isDead_ = true;
	}
};

void EnemyBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}

void EnemyBullet::OnCollision() { 
	isDead_ = true; 
}

Vector3 EnemyBullet::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}