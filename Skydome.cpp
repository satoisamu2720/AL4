#include "Skydome.h"

void Skydome::Initialize(Model* model) { 
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
}

void Skydome::Update() { 
	
}

void Skydome::Draw(ViewProjection view) { 
	model_->Draw(worldTransform_, view); 
}