#pragma once
#include "Model.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "assert.h"
 


class Enemy {
public:

	///
	///
	///
	///
	///
	void Initialize(Model* model, const Vector3& position);

	///
	///
	///
	void Update();

	///
	///
	///
	void Draw(ViewProjection view);


	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	
};
