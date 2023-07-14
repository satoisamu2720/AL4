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

void EnemyBullet::Updarte() {
	worldTransform_.UpdateMatrix();

	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;
};

void EnemyBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}