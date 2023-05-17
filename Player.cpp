#include "Player.h"
#include <cassert>


void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	input_ = Input::GetInstance();
};

void Player::Update() {
	worldTransform_.TransferMatrix();

	Vector3 move = {0, 0, 0};

	
};

void Player::Draw(ViewProjection view) { model_->Draw(worldTransform_, view, textureHandle_); };
