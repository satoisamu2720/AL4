#include "PlayerBullet.h"
#include "assert.h"
#include "VectraCalculation.h"



void PlayerBullet::Initialize(Model* model, const Vector3& position) { 
	
	assert(model);
	
	//テクスチャ読み込み
	texturehandle_ = TextureManager::Load("kamata.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	
	
};


void PlayerBullet::Updarte(){
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

};


void PlayerBullet:: Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, texturehandle_);
}