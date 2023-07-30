#include "Skydome.h"

void Skydome::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransfome_.Initialize();
	worldTransfome_.scale_ = {100.0f, 100.0f, 100.0f};
	
}

void Skydome::Update() {
}

void Skydome::Draw(ViewProjection& view) { 
	model_->Draw(worldTransfome_, view); 
}
