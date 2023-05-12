#include "TextureManager.h"
#include "WorldTransform.h"
#include "Model.h"
#include "input.h"
#pragma once

class Player {
public:
	///
	///
	///
	/// 
	/// 
	void Initialize(Model* model, uint32_t textureHandle);


	///
	///
	/// 
	void Update();

	///
	///
	/// 
	void Draw(ViewProjection view);
	
	
	private:
	WorldTransform worldTransform_;
	    Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;
};
