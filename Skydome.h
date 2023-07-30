#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
    /// <summary>
/// 天球
/// </summary>
class Skydome {
public:
	
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection view);

	private:
	WorldTransform worldTransform_;
	    Model* model_ = nullptr;
};
