#pragma once
#include "PlayerBullet.h"
#include "assert.h"
#include "VectraCalculation.h"



void PlayerBullet::Initialize(Model* model, const Vector3& position) { 
	
	assert(model);
	
	//テクスチャ読み込み
	texturehandle_ = TextureManager::Load("genshin.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	
	
};


void PlayerBullet::Updarte(){ worldTransform_.UpdateMatrix();
	    

};


void PlayerBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}