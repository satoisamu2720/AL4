#pragma once
#include <cassert>
#include "Model.h"
#include "WorldTransform.h"
class Skydome {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& view);

public:
	WorldTransform worldTransfome_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
